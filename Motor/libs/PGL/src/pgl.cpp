#include "PGL.h"


#include "basic\Circle.h"
#include "Logger.h"

typedef unsigned int uint;

namespace pgl {

    Application::Application(uint16_t width, uint16_t height, const char* title, uint16_t version_major, uint16_t version_minor)
        : m_Width(width), m_Height(height), m_Title(title),
        m_VERSION_MAJOR(version_major), m_VERSION_MINOR(version_minor)
    {
        assert(sizeof(GLuint) == sizeof(uint));

        Logger l(Logger::Filter::FILTER_ERROR);

        // setup glfw
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version_major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version_minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        const char* glsl_version = "#version 330 core";

        m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);

        if (!m_Window) // == nullptr
        {
            l.Log("Unable to create GLFW window\n", Logger::Log_Level::ERROR, Logger_Color{ Logger_Color::Colors::RED });
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(m_Window);
        glfwSwapInterval(1);

        // make sure glad is initialized
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            l.Log("Unable to initialize GLAD\n", Logger::Log_Level::ERROR, Logger_Color{ Logger_Color::Colors::RED });
            return;
        }

        GLCall(glViewport(0, 0, width, height));
        glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);




        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        m_IO = std::addressof(ImGui::GetIO());
        //ImGuiIO& io = ImGui::GetIO(); (void)io;
        m_IO->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        m_IO->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        m_IO->ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        m_IO->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
        //m_IO->ConfigViewportsNoAutoMerge = true;
        //m_IO->ConfigViewportsNoTaskBarIcon = true;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (m_IO->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);
    }

    Application::~Application()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwTerminate();
    }

    void Application::Run()
    {
        Update(1.0f / m_IO->Framerate);


        GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
        m_Renderer.Clear();
        

        Logger l(Logger::FILTER_INFO);
        l.Log("test test test\n\n\n", Logger::Log_Level::WARN);
        //std::cout << "test 1\n";
        OnRender();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        OnImGuiRender();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //ImGuiIO& io = ImGui::GetIO(); (void)io;
        if (m_IO->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }


        glfwSwapBuffers(m_Window);
    }


    void Application::Update(float dt)
    {
        glfwPollEvents();

        // handle inputs
        ProcessInputs();

        // call each object's Update function
        const float vertices[] = {

            -0.5f, -0.5f,  0.0f,
             0.5f, -0.5f,  0.0f,
             0.0f,  0.5f,  0.0f
        };




    }

    void Application::OnRender()
    {
        // some stuff
        // call each object's Render functions
        Circle c(glm::vec2{ 0,0 }, 10);
        c.OnRender();




        float vertices[] = {
            -0.5f, -0.5f,  0.0f,   // vertex 1
            -0.5f,  0.5f,  0.0f,   // vertex 2
             0.5f,  0.5f,  0.0f,   // vertex 3
             0.5f, -0.5f,  0.0f    // vertex 4
        };

        uint indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        // vertex buffer 
        VertexBuffer m_VBO(vertices, sizeof(vertices), GL_STATIC_DRAW);

        // vertex layout
        VertexBufferLayout layout;
        layout.Push<float>(3);

        // vertex array
        VertexArray m_VAO;
        m_VAO.AddBuffer(m_VBO, layout);


        // index array
        IndexBuffer m_IBO(indices, 6);

        Renderer renderer;


        // Shaders

        const char* vert_source = "#version 330 core\n"
            "layout (location = 0) in vec3 pos;\n"
            "out vec4 vertexColor;\n"
            "void main()\n"
            "{\n"
            "    gl_Position = vec4(pos, 1.0);\n"
            "    vertexColor = vec4(1, 0.0, 0.0, 1.0);\n"
            "}";

        const char* frag_source =
            "#version 330 core\n"
            "out vec4 FragColor;\n"
            "in vec4 vertexColor;\n"
            "void main()\n"
            "{\n"
            "    FragColor = vec4(1.0, 0.0, 0.0, 1.0);"
            "    //FragColor = vertexColor;\n"
            "}";


        Shader m_Shader(vert_source, frag_source, false);
        m_Shader.Bind();

        m_Renderer.Draw(m_VAO, m_IBO, m_Shader);

    }

    void Application::OnImGuiRender()
    {
        ImGui::ShowDemoWindow(); // Show demo window! :)

        // call each object's ImGuiRender functions


        {
            ImGui::Begin("Specs");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / m_IO->Framerate, m_IO->Framerate);
            ImGui::End();
        }
    }


    void Application::ProcessInputs()
    {
        if (ImGui::IsKeyPressed(ImGuiKey_Escape))
        {
            glfwSetWindowShouldClose(m_Window, true);
        }
    }

};



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    GLCall(glViewport(0, 0, width, height));
}
