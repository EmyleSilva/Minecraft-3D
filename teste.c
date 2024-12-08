#include <GL/glut.h>
#include <stdlib.h>

int largura = 500, altura = 500;
float a[3] = {-4.0, 4.0, -4.0};  // Posição da câmera

void Iniciar(void) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(a[0], a[1], a[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(10.0, (GLfloat)largura / (GLfloat)altura, 1.0, 20.0);
}

void Casinha(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Limpeza do buffer
    Iniciar();  // Chama a função de inicialização da câmera
    glEnable(GL_DEPTH_TEST);  // Ativa o teste de profundidade

    // Eixos cartesianos
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 1.0f);  // Eixo X
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.7f, 0.0f, 0.0f);
    
    glColor3f(1.0f, 0.0f, 0.0f);  // Eixo Y
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.5f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);  // Eixo Z
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.7f);
    glEnd();

    // Parede de trás
    glBegin(GL_POLYGON);
    glColor3f(0.6f, 0.0f, 0.0f);  // Vermelha
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.2f, 0.0f);
    glVertex3f(0.2f, 0.3f, 0.0f);
    glVertex3f(0.4f, 0.2f, 0.0f);
    glVertex3f(0.4f, 0.0f, 0.0f);
    glEnd();

    // Parede esquerda
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.6f);  // Azul
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.4f);
    glVertex3f(0.0f, 0.2f, 0.4f);
    glVertex3f(0.0f, 0.2f, 0.0f);
    glEnd();

    // Telhado
    glBegin(GL_QUAD_STRIP);
    glColor3f(0.0f, 0.6f, 0.0f);  // Verde
    glVertex3f(0.0f, 0.2f, 0.0f);
    glVertex3f(0.0f, 0.2f, 0.4f);
    glVertex3f(0.2f, 0.3f, 0.0f);
    glVertex3f(0.2f, 0.3f, 0.4f);
    glVertex3f(0.4f, 0.2f, 0.0f);
    glVertex3f(0.4f, 0.2f, 0.4f);
    glEnd();

    // Parede da frente
    glBegin(GL_POLYGON);
    glColor3f(0.6f, 0.6f, 0.6f);  // Cinza
    glVertex3f(0.0f, 0.0f, 0.4f);
    glVertex3f(0.4f, 0.0f, 0.4f);
    glVertex3f(0.4f, 0.2f, 0.4f);
    glVertex3f(0.2f, 0.3f, 0.4f);
    glVertex3f(0.0f, 0.2f, 0.4f);
    glEnd();

    // Parede direita
    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.8f, 0.0f);  // Amarelo
    glVertex3f(0.4f, 0.0f, 0.0f);
    glVertex3f(0.4f, 0.0f, 0.4f);
    glVertex3f(0.4f, 0.2f, 0.4f);
    glVertex3f(0.4f, 0.2f, 0.0f);
    glEnd();

    glFlush();  // Executa os comandos de desenho
}

void Teclado(unsigned char key, int x, int y) {
    switch (key) {
        case 27:  // Tecla ESC
            exit(0);
            break;
        case 'a':
            a[0] = a[0] - 0.2;  // Move a câmera para a esquerda
            break;
        case 's':
        a[0] = a[0] + 0.2;
        break;

    }
    glutPostRedisplay();  // Atualiza a tela
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);  // Modo de exibição com profundidade
    glutInitWindowSize(largura, altura);  // Define o tamanho da janela
    glutInitWindowPosition(50, 50);  // Posição inicial da janela
    glutCreateWindow("Casinha 3D ... ");  // Título da janela

    glClearColor(0.0, 0.0, 0.0, 0.0);  // Cor de fundo
    glEnable(GL_DEPTH_TEST);  // Habilita o teste de profundidade

    glutDisplayFunc(Casinha);  // Função de exibição
    glutKeyboardFunc(Teclado);  // Função de teclado
    glutMainLoop();  // Inicia o loop principal do OpenGL

    return 0;
}
