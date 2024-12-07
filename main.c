#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION //Usado para importar as imagens de textura
#include "stb_image.h"

#define EIXO_X 0
#define EIXO_Y 1
#define EIXO_Z 2

int largura = 1024, altura = 1024;
float a[3] = {6.0, 4.0, 4.0};

GLint tex_id[3]; //Armazena os IDs de textura

/**
 * @brief Carrega uma textura
 * 
 * @param path Caminho para a textura
 * @param texId Id da textura
 */
void load(const char *path, int texId)
{
    //Carrega a textura
    int largura, altura, canal;
    unsigned char *data = stbi_load(path, &largura, &altura, &canal, 0);

    if (!data)
    {
        printf("Erro ao carregar a textura.\n");
        exit(1);
    }

    glBindTexture(GL_TEXTURE_2D, tex_id[texId]); //Associa o ID ao tipo de textura 2D 

    //Envia a textura para o openGL (fica armazenada)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, largura, altura, 0, canal == 4? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
    //Configura os parâmetros da textura (para ajustar corretamente ao cubo)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //Libera a imagem
    stbi_image_free(data);
}

void Iniciar() {
    glGenTextures(3, tex_id); //Gera identificadores para as texturas 
    //Carrega as texturas
    load("img/pedra.jpeg", 0);
    load("img/madeira.jpg", 1);
    load("img/madeira(lados).png", 2);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(a[0], a[1], a[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(20.0,largura/altura,1.0,20.0);
}

/*void desenha_cubo(int id)
{   
    //Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);
    //Vincula a textura
    glBindTexture(GL_TEXTURE_2D, tex_id[id]);

     //Define como a cor e a textura se comportam (nesse caso, usa replace para usar somente a textura e descartar a cor)
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    //glColor3f(0.0f,0.0f,0.6f); 
    glBegin( GL_QUADS ); //Face y-z, com x = 0.0
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f,0.0f,0.0f); //Inferior esquerdo
        glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f,0.0f,0.2f); //Inferior direito
        glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f,0.2f,0.2f); //Superior direito
        glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f,0.2f,0.0f); //Superior esquerdo
    glEnd();

    //glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS); //Face x-z, com y = 0.0
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f); //Inferior esquerdo
        glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.2f); //Inferior direito
        glTexCoord2f(1.0f, 1.0f); glVertex3f(0.2f, 0.0f, 0.2f); //Superior direito
        glTexCoord2f(0.0f, 1.0f); glVertex3f(0.2f, 0.0f, 0.0f); //Superior esquerdo
    glEnd();

    glBegin(GL_QUADS); //Face x-z, com y = 0.2
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.2f, 0.0f); //Inferior esquerdo
        glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.2f, 0.2f); //Inferior direito
        glTexCoord2f(1.0f, 1.0f); glVertex3f(0.2f, 0.2f, 0.2f); //Superior direito
        glTexCoord2f(0.0f, 1.0f); glVertex3f(0.2f, 0.2f, 0.0f); //Superior esquerdo
    glEnd();

    //glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS); //Face y-x, com z = 0.2 
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.2f); //Inferior esquerdo
        glTexCoord2f(1.0f, 0.0f); glVertex3f(0.2f, 0.0f, 0.2f); //Inferior direito
        glTexCoord2f(1.0f, 1.0f); glVertex3f(0.2f, 0.2f, 0.2f); //Superior direito
        glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.2f, 0.2f); //Superior esquerdo
    glEnd();

    glBegin(GL_QUADS); //Face y-x, com z = 0.0 
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f); //Inferior esquerdo
        glTexCoord2f(1.0f, 0.0f); glVertex3f(0.2f, 0.0f, 0.0f); //Inferior direito
        glTexCoord2f(1.0f, 1.0f); glVertex3f(0.2f, 0.2f, 0.0f); //Superior direito
        glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.2f, 0.0f); //Superior esquerdo
    glEnd();

    //glColor3f(0.0f,0.0f,0.6f); 
    glBegin( GL_QUADS ); //Face y-z, com x = 2.0
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.2f,0.0f,0.0f); //Inferior esquerdo
        glTexCoord2f(1.0f, 0.0f); glVertex3f(0.2f,0.0f,0.2f); //Inferior direito
        glTexCoord2f(1.0f, 1.0f); glVertex3f(0.2f,0.2f,0.2f); //Superior direito
        glTexCoord2f(0.0f, 1.0f); glVertex3f(0.2f,0.2f,0.0f); //Superior esquerdo
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0); //Desabilita o uso de texturas em outros objetos
    glDisable(GL_TEXTURE_2D); 
}*/

void desenha_cubo(int id)
{   
    // Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);
    // Vincula a textura
    glBindTexture(GL_TEXTURE_2D, tex_id[id]);

    // Define como a cor e a textura se comportam
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // Face y-z, com x = -0.1
    glBegin(GL_QUADS); 
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.1f, -0.1f, -0.1f); // Inferior esquerdo
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.1f, -0.1f,  0.1f); // Inferior direito
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.1f,  0.1f,  0.1f); // Superior direito
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.1f,  0.1f, -0.1f); // Superior esquerdo
    glEnd();

    // Face x-z, com y = -0.1
    glBegin(GL_QUADS); 
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.1f, -0.1f, -0.1f); // Inferior esquerdo
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.1f, -0.1f,  0.1f); // Inferior direito
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.1f, -0.1f,  0.1f); // Superior direito
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.1f, -0.1f, -0.1f); // Superior esquerdo
    glEnd();

    // Face x-z, com y = 0.1
    glBegin(GL_QUADS); 
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.1f,  0.1f, -0.1f); // Inferior esquerdo
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.1f,  0.1f,  0.1f); // Inferior direito
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.1f,  0.1f,  0.1f); // Superior direito
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.1f,  0.1f, -0.1f); // Superior esquerdo
    glEnd();

    // Face y-x, com z = 0.1
    glBegin(GL_QUADS); 
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.1f, -0.1f,  0.1f); // Inferior esquerdo
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.1f, -0.1f,  0.1f); // Inferior direito
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.1f,  0.1f,  0.1f); // Superior direito
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.1f,  0.1f,  0.1f); // Superior esquerdo
    glEnd();

    // Face y-x, com z = -0.1
    glBegin(GL_QUADS); 
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.1f, -0.1f, -0.1f); // Inferior esquerdo
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.1f, -0.1f, -0.1f); // Inferior direito
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.1f,  0.1f, -0.1f); // Superior direito
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.1f,  0.1f, -0.1f); // Superior esquerdo
    glEnd();

    // Face y-z, com x = 0.1
    glBegin(GL_QUADS); 
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.1f, -0.1f, -0.1f); // Inferior esquerdo
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.1f, -0.1f,  0.1f); // Inferior direito
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.1f,  0.1f,  0.1f); // Superior direito
        glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.1f,  0.1f, -0.1f); // Superior esquerdo
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0); // Desabilita o uso de texturas em outros objetos
    glDisable(GL_TEXTURE_2D); 
}

void transform(int texID, float x, float y, float z)
{
    glPushMatrix(); 
        glTranslatef(x, y, z); 
        desenha_cubo(texID); 
    glPopMatrix(); 
}

void desenha_cubos_enfileirados(int quantidade, float distancia, int texID, int EIXO)
{
    if (EIXO == EIXO_X){
        float z = 0.0f, y = 0.0f;
        for (int i = 0; i < quantidade; i++)
        {
            transform(texID, (float)i*distancia, y, z);
            z-=distancia;
            y-=distancia;
        }
    }else if (EIXO == EIXO_Y){
        float x = 0.0f, z = 0.0f;
        for (int i = 0; i < quantidade; i++)
        {
            transform(texID, x, (float)i*distancia, z);
            z-=distancia;
            x-=distancia;
        }
    }else {
        float x = 0.0f, y = 0.0f;
        for (int i = 0; i < quantidade; i++)
        {
            transform(texID, x, y, (float)i*distancia);
            x-=distancia;
            y-=distancia;
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Iniciar();
    glEnable(GL_DEPTH_TEST);
    
    glBegin( GL_LINES ); //Eixos cartesianos
        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(0.7f,0.0f,0.0f);
        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(0.0f,0.5f,0.0f);
        glColor3f(0.0f,1.0f,0.0f);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(0.0f,0.0f,0.7f);
    glEnd();
    
    desenha_cubo(1);
    
    // desenha_cubos_enfileirados(5, 0.15f, 2, EIXO_X);
    // desenha_cubos_enfileirados(5, 0.15f, 2, EIXO_Z);
    glFlush();
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
   glutInitWindowSize(largura, altura);
   glutInitWindowPosition(50, 50);
   glutCreateWindow(argv[1]);
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glutDisplayFunc(display);
   //glutKeyboardFunc(teclado);
   glutMainLoop();
   return 0;
}
