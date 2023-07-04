#include "Renderer.h"


uint32_t Height = 1920;
uint32_t Width = 1080;

float Vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

unsigned int Indices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
};


glm::vec3 PyramidPositions[4] = {
    glm::vec3(0.0f , -0.5f , -5.0f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
};

glm::mat4 Model = glm::mat4(1.0f);
glm::mat4 View = glm::mat4(1.0f);
glm::mat4 Proj = glm::mat4(1.0f);

static bool openDockspace = true;

Renderer::Renderer()
{

    shader = new Shader("../Res/Shader/Basic.Shader");


    
   
    vertexbuffer = new VertexBuffer();
    indexbuffer = new IndexBuffer();
    vertexArray = new VertexArray();

    vertexArray->Bind();

    vertexbuffer->Bind();
    vertexbuffer->AddBufferData(Vertices, sizeof(Vertices));

    indexbuffer->Bind();
    indexbuffer->AddBufferData(Indices, sizeof(Indices));
    
    Layout.AddLayoutData(GL_FLOAT, 3);
    Layout.AddLayoutData(GL_FLOAT, 3);
    Layout.AddLayoutData(GL_FLOAT, 2);
    vertexArray->AddBuffer(vertexbuffer, Layout);

    vertexArray->UnBind();

    BrickTexture = new Texture("../Res/Texture/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    BrickTexture->TextureUnit(shader, "tex0", 0);



}

void Renderer::Draw()
{

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();




    shader->Bind(); 
    vertexArray->Bind();
    BrickTexture->Bind();

    Model = glm::mat4(1.0f);
    Proj = glm::mat4(1.0f);



    //Docspace ImGui
   /* {
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

         We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
         because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

         When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
         and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

         Important: note that we proceed even if Begin() returns false (aka window is collapsed).
         This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
         all active windows docked into it will lose their parent and become undocked.
         We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
         any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &openDockspace, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

         Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }


        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Options"))
            {
                 Disabling fullscreen would allow the window to be moved to the front of other windows,
                 which we can't undo at the moment without finer window depth/z control.
                ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
                ImGui::MenuItem("Padding", NULL, &opt_padding);
                ImGui::Separator();

                if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
                if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
                if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
                if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
                if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
                ImGui::Separator();

                if (ImGui::MenuItem("Close", NULL, false))
                    openDockspace = false;
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }


      

        ImGui::End();
    }
   */

    ImGui::Begin("Demo window");
    ImGui::Button("Hello!");
    for (int i = 0; i < 4; i++)
    {
        std::string Pos = "Position " + std::to_string(i);
        ImGui::SliderFloat3(Pos.c_str(), &(PyramidPositions[i].x), -10.0f, 10.0f);
    }
    ImGui::End();

    View = glm::lookAt(glm::vec3(10, 0.0, 5), glm::vec3(0.0, -0.5, -0.5), glm::vec3(0.0, 1.0, 0.0));

    Model = glm::rotate(Model, glm::radians(Rotation), glm::vec3(0.0f, 1.0f, 0.0f));

    Proj = glm::perspective(glm::radians(45.0f),(float)Height/(float)Width , 0.1f, 100.0f);

    unsigned int ModelLocation = shader->GetUniformLocation("model");
    glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, glm::value_ptr(Model));

    unsigned int ProjLocation = shader->GetUniformLocation("proj");
    glUniformMatrix4fv(ProjLocation, 1, GL_FALSE, glm::value_ptr(Proj));

    for (int i = 0; i < 4; i++)
    {
        View = glm::mat4(1.0f);
        View = glm::translate(View, PyramidPositions[i]);
        unsigned int ViewLocation = shader->GetUniformLocation("view");
        glUniformMatrix4fv(ViewLocation, 1, GL_FALSE, glm::value_ptr(View));
        glDrawElements(GL_TRIANGLES, sizeof(Indices) / sizeof(int), GL_UNSIGNED_INT, 0);
    }


    // Render dear imgui into screen
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

Renderer::~Renderer()
{
    delete vertexbuffer;
    delete indexbuffer;
    delete vertexArray;
    delete BrickTexture;
    delete shader;
}
