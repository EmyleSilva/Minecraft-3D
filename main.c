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
float a[3] = {0.0, 0.0, 6.0};
GLint tex_id[4]; //Armazena os IDs de textura

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
    glGenTextures(4, tex_id); //Gera identificadores para as texturas 
    //Carrega as texturas
    load("img/stone.jpg", 0);
    load("img/madeira.jpg", 1);
    load("img/madeira(lados).png", 2);
    load("img/vidro.png", 3);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,largura/altura,1.0,20.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(a[0], a[1], a[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
}

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


void desenha_cubos_enfileirados(int quantidade, float x, float y, float z, float distancia, int texID, int EIXO)
{
    if (EIXO == EIXO_X){
        for (int i = 0; i < quantidade; i++)
        {
            transform(texID, x + (float)i*distancia, y, z);
        }
    }else if (EIXO == EIXO_Y){
        for (int i = 0; i < quantidade; i++)
        {
            transform(texID, x, y + (float)i*distancia, z);
        }
    }else {
        for (int i = 0; i < quantidade; i++)
        {
            transform(texID, x, y, z + (float)i*distancia);
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
        glVertex3f(7.0f,0.0f,0.0f);
        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(0.0f,7.0f,0.0f);
        glColor3f(0.0f,1.0f,0.0f);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(0.0f,0.0f,7.0f);
    glEnd();
    
    //transform(1, 0.4, 0, 0);
    //transform(1, 0.6, 0, 0);

    desenha_cubos_enfileirados(5, 0.0, 0.0 , 0.0 , 0.2f, 0, EIXO_X);
    desenha_cubos_enfileirados(5, 0.0, 0.2 , 0.0 , 0.2f, 3, EIXO_X);
    desenha_cubos_enfileirados(5, 0.0, 0.4 , 0.0 , 0.2f, 1, EIXO_X);

    //transform(1, 0.0, 0.2, 0.6);
    //for(int i = 0; i < 10; i++)
        //transform(1, i * 0.2, 0.0, 0.0);


    glutSwapBuffers();
}

void Teclado(unsigned char key, int x, int y) {
   switch (key) {
        case 27:
            exit(0);
            break;
        case 'q': a[0]=a[0]-0.2;
            break;
        case 'w': a[0]=a[0]+0.2; // Troquei 's' por 'd' para movimento à direita
            break;
        case 'a': a[1]=a[1]-0.2;
            break;
        case 's': a[1]=a[1]+0.2;
            break;
        case 'z': a[2]=a[2]-0.2; // Move para frente
            break;
        case 'x': a[2]=a[2]+0.2; // Move para trás (usei 'e' para o movimento para trás)
            break;
   }
   glutPostRedisplay();
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
   glutInitWindowSize(largura, altura);
   glutInitWindowPosition(50, 50);
   glutCreateWindow(argv[1]);
   glClearColor(0.0, 0.0, 0.0, 0.0);
   Iniciar();
   glutDisplayFunc(display);
   glutKeyboardFunc(Teclado);
   glutMainLoop();
   return 0;
}
