#include "Renderer.h"

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
    shader->Bind(); 
    vertexArray->Bind();
    BrickTexture->Bind();


    glm::mat4 Model = glm::mat4(1.0f);
    glm::mat4 View = glm::mat4(1.0f);
    glm::mat4 Proj = glm::mat4(1.0f);

    Model = glm::rotate(Model, (float)glfwGetTime()*glm::radians(Rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    View = glm::translate(View, glm::vec3(0.0f , -0.5f , -2.0f));
    Proj = glm::perspective(glm::radians(45.0f), (float)(800/800), 0.1f, 100.0f);

    unsigned int ModelLocation = shader->GetUniformLocation("model");
    glUniformMatrix4fv(ModelLocation, 1, GL_FALSE, glm::value_ptr(Model));

    unsigned int ViewLocation = shader->GetUniformLocation("view");
    glUniformMatrix4fv(ViewLocation, 1, GL_FALSE, glm::value_ptr(View));

    unsigned int ProjLocation = shader->GetUniformLocation("proj");
    glUniformMatrix4fv(ProjLocation, 1, GL_FALSE, glm::value_ptr(Proj));

    glDrawElements(GL_TRIANGLES,sizeof(Indices)/sizeof(int), GL_UNSIGNED_INT, 0);

}

Renderer::~Renderer()
{
    delete vertexbuffer;
    delete indexbuffer;
    delete vertexArray;
    delete BrickTexture;
    delete shader;
}
