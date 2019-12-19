#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#define numLinha 16

void CriaMenu();
void colisionAction();

typedef struct{
  GLfloat r;
  GLfloat g;
  GLfloat b;
  GLfloat a;
}color;//struct pra cor

typedef struct{
  GLfloat x;
  GLfloat y;
}vetor;//struct pra coordenadas


char texto[30],ganhou[30];//vetor de char pra exibir textos na tela
int contVidas = 4, flag = 10;//cont de vida e flag de vitoria
    vetor Centro, aux;//coordenadas do centro(?) e auxiliar
    vetor vectLinha1[20], vectLinha2[20], vectMisc[4];//vetor de coordenadas das linhas e dos limites inicial e final
float xr = 50, yr = 0;//variaveis usadas pra desenhar o quadrado

color colorQuad, colorBack, colorLab;//valores RGB para as cores do quadrado, fundo e labirinto

//funcao do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
         if (state == GLUT_DOWN)
            CriaMenu();

    glutPostRedisplay();
}

float unidade = 10.0f;//funcao usada na atualiza��o das coordenadas do objeto quando uma das setas � pressunada
void predio(void)
{


	//glLineWidth(2);
	glColor3f(0.6,0.6,0.6);

	//Corpo do predio  ABCD-> Retangulo
	glBegin(GL_QUADS);
		glVertex2f(-20.0f,0.0f); //A
		glVertex2f(-20.0f,40.0f);//B
		glVertex2f(0.0f,40.0f); //C
		glVertex2f(0.0f,0.0f);  //D
    glEnd();

    glColor3f(0.8,0.8,0.8);
		//Porta, DEFINIR COR
		glBegin(GL_QUADS);
		glVertex2f(-12.0f,0.0f); //E
		glVertex2f(-10.0f,0.0f);//F
		glVertex2f(-12.0f,2.0f); //G
		glVertex2f(-10.0f,2.0f);  //H
    glEnd();

glColor3f(0.3,0.3,0.3);

        //Janela, falta DEFINIR A COR
    glBegin(GL_QUADS);
		glVertex2f(-18.0f,22.0f); //I
		glVertex2f(-14.0f,22.0f);//J
		glVertex2f(-14.0f,20.0f); //K
		glVertex2f(-18.0f,20.0f);  //L
    glEnd();

glColor3f(0.4,0.4,0.4);
		//Traco na janela acima, para separar a janela.
    glBegin(GL_LINES);
		glLineWidth(2);//MEXA NISSO SE ALTERAR OUTRA COISA.
		//vertical
		glVertex2f(-16.0f,22.0f); //A
		glVertex2f(-16.0f,20.0f);//B

		//HORIZONTAL
		glVertex2f(-14.0f,21.0f); //C
		glVertex2f(-18.0f,21.0f);  //D
    glEnd();


}
//funcao teclado setas
void TeclasEspeciais(int key, int x, int y)
{
    switch (key){
        case GLUT_KEY_RIGHT:
            xr+=unidade;
            break;

        case GLUT_KEY_LEFT:
            xr-=unidade;
        break;

        case GLUT_KEY_UP:
            yr+=unidade;
            break;

        case GLUT_KEY_DOWN:
            yr-=unidade;
        break;

        default:
         break;
    }
    glutPostRedisplay();
}

//funcao pra desenhar o quadrado
void rect(){
    glBegin(GL_QUADS);
    glVertex2f(-20.0f + xr, 20.0f + yr);
    glVertex2f( -20.0f + xr,-20.0f+ yr);
    glVertex2f( 20.0f+ xr, -20.0f+ yr);
    glVertex2f( 20.0f+ xr, 20.0f + yr);
    glEnd();

}


//funcao pra criar o labirinto
void labirinto(){
    predio();
	int i;
    glLineWidth(2);//tamanho da linha
    glBegin(GL_LINE_STRIP);//linhas consecutivas
    for(i=0; i<numLinha;i++){
        glVertex2f(vectLinha1[i].x, vectLinha1[i].y);
    }

      glEnd();

     glBegin(GL_LINE_STRIP);
    for(i=0; i<numLinha;i++){
        glVertex2f(vectLinha2[i].x, vectLinha2[i].y);
    }
      glEnd();

    glBegin(GL_LINE_STRIP);//linha que une as duas linhas principais no come�o
    glVertex2f(vectMisc[0].x, vectMisc[0].y);
    glVertex2f(vectMisc[1].x, vectMisc[1].y);
    glEnd();

    glPushMatrix();//salva contexto
    glColor3f(0.4,1,0);
    glBegin(GL_LINE_STRIP);//linha de chegada
    glVertex2f(vectMisc[2].x, vectMisc[2].y);
    glVertex2f(vectMisc[3].x, vectMisc[3].y);
    glEnd();
    glPopMatrix();//retoma o contexto

    colisionAction();//chama a fun��o de a��o de colis�o

}

//fun��o que realiza a��es se houve uma colis�o
void colisionAction(){
    Centro.x = xr;
    Centro.y = yr;

        if((colision(Centro,20, vectLinha1[0], vectLinha1[1])) |
           (colision(Centro,20, vectLinha1[1], vectLinha1[2])) |
           (colision(Centro,20, vectLinha1[2], vectLinha1[3])) |
           (colision(Centro,20, vectLinha1[3], vectLinha1[4])) |
           (colision(Centro,20, vectLinha1[4], vectLinha1[5])) |
           (colision(Centro,20, vectLinha1[5], vectLinha1[6])) |
           (colision(Centro,20, vectLinha1[6], vectLinha1[7])) |
           (colision(Centro,20, vectLinha1[7], vectLinha1[8])) |
           (colision(Centro,20, vectLinha1[8], vectLinha1[9])) |
           (colision(Centro,20, vectLinha1[9], vectLinha1[10])) |
           (colision(Centro,20, vectLinha1[10], vectLinha1[11])) |
           (colision(Centro,20, vectLinha1[11], vectLinha1[12])) |
           (colision(Centro,20, vectLinha1[12], vectLinha1[13])) |
           (colision(Centro,20, vectLinha1[13], vectLinha1[14])) |
           (colision(Centro,20, vectLinha1[14], vectLinha1[15])) |
           (colision(Centro,20, vectLinha2[0], vectLinha2[1])) |
           (colision(Centro,20, vectLinha2[1], vectLinha2[2])) |
           (colision(Centro,20, vectLinha2[2], vectLinha2[3])) |
           (colision(Centro,20, vectLinha2[3], vectLinha2[4])) |
           (colision(Centro,20, vectLinha2[4], vectLinha2[5])) |
           (colision(Centro,20, vectLinha2[5], vectLinha2[6])) |
           (colision(Centro,20, vectLinha2[6], vectLinha2[7])) |
           (colision(Centro,20, vectLinha2[7], vectLinha2[8])) |
           (colision(Centro,20, vectLinha2[8], vectLinha2[9])) |
           (colision(Centro,20, vectLinha2[9], vectLinha2[10])) |
           (colision(Centro,20, vectLinha2[10], vectLinha2[11])) |
           (colision(Centro,20, vectLinha2[11], vectLinha2[12])) |
           (colision(Centro,20, vectLinha2[12], vectLinha2[13])) |
           (colision(Centro,20, vectLinha2[13], vectLinha2[14])) |
           (colision(Centro,20, vectLinha2[14], vectLinha2[15])) |
           (colision(Centro,20, vectMisc[0], vectMisc[1]))
        ){
            contVidas--;
            yr=0;
            xr=50;
            printf("Colidiu!");

            if(!contVidas){
                flag = 0;
                contVidas = 4;
            }

        }
        if((colision(Centro,20,vectMisc[2], vectMisc[3]))){
            flag = 1;
            yr=0;
            xr=50;
            contVidas = 4;
        }

}


//func�o que faz os calculos pra saber se ocorreu uma colis�o
int colision(vetor Centro,int Tamanho,vetor linePosA, vetor linePosB){

    float A, B , C, D;
    A = Centro.x - linePosA.x;
    B = Centro.y - linePosA.y ;
    C = linePosB.x - linePosA.x;
    D = linePosB.y - linePosA.y;

    float dot = A * C + B * D;
    float len = C * C + D * D;
    float para = dot / len;

    float x,y;

    if(para < 0){
        x = linePosA.x;
        y = linePosA.y;
    }else if(para > 1){
        x = linePosB.x;
        y = linePosB.y;
    }else{
        x = linePosA.x + para * C;
        y = linePosA.y + para * D;
    }
    float xdif = Centro.x - x;
    float ydif = Centro.y - y;
    float hypo = sqrt((xdif * xdif) + (ydif * ydif));
    if (hypo < Tamanho){
        return 1;
    }
    return 0;
}

//desenha texto com linhas
void DesenhaTextoStroke(void *font, char *string)
{
	while(*string)
		glutStrokeCharacter(GLUT_STROKE_ROMAN,*string++);
}
void coracao (void)
{
    glScalef(2,2,0);
    glColor3f(1, 0, 0);//  topo
	glBegin(GL_TRIANGLE_FAN);

    glVertex2f( 0.0f , 15.0f);//A
    glVertex2f( -10.0f,15.0f);//B
    glVertex2f( -9.0f, 19.0f);//C
    glVertex2f(-8.0f,  20.0f);//D
    glVertex2f(-7.0f,  21.0f);//D
    glVertex2f(-6.0f,  22.0f);//D
    glVertex2f(-4.0f,  23.0f);//D
    glVertex2f(-2.0f,  24.0f);//D
    //glVertex2f(0.0f,   25.0f);//D
    glVertex2f(2.0f,  24.0f);//D
    glVertex2f(4.0f,  23.0f);//D
    glVertex2f(6.0f,  22.0f);//D
    glVertex2f(7.0f,  21.0f);//D
    glVertex2f(8.0f,  20.0f);//D
    glVertex2f( 9.0f, 19.0f);//C
    glVertex2f( 10.0f,15.0f);//B

    glEnd();
    glTranslatef(18.0f,0.0f,0.0f);

	glBegin(GL_TRIANGLE_FAN);

    glVertex2f( 0.0f , 15.0f);//A
    glVertex2f( -10.0f,15.0f);//B
    glVertex2f( -9.0f, 19.0f);//C
    glVertex2f(-8.0f,  20.0f);//D
    glVertex2f(-7.0f,  21.0f);//D
    glVertex2f(-6.0f,  22.0f);//D
    glVertex2f(-4.0f,  23.0f);//D
    glVertex2f(-2.0f,  24.0f);//D
    //glVertex2f(0.0f,   25.0f);//D
    glVertex2f(2.0f,  24.0f);//D
    glVertex2f(4.0f,  23.0f);//D
    glVertex2f(6.0f,  22.0f);//D
    glVertex2f(7.0f,  21.0f);//D
    glVertex2f(8.0f,  20.0f);//D
    glVertex2f( 9.0f, 19.0f);//C
    glVertex2f( 10.0f,15.0f);//B
    glEnd();

    glBegin(GL_TRIANGLES);
     glVertex2f( 10.0f , 15.0f);//A
    glVertex2f( -28.0f,15.0f);//B
    glVertex2f( -9.0f, -8.0f);//C

    glEnd();




}


//desenha texto com bitmap
void DesenhaTexto(void *font, char *string)
{
	while(*string)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*string++);
}

//fun��o de desenhar
void Desenha(void)
{


    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glColor3f(colorQuad.r,colorQuad.g,colorQuad.b);


    glPushMatrix();

	glTranslatef(-600.0f, -300.0f,0.0f);
    rect();

    glColor3f(colorLab.r,colorLab.g,colorLab.b);
    labirinto();

    glPopMatrix();


    glPushMatrix();
    garrafa();
    glColor3f(0.2,0.8,0.6 );
     glScalef(1.2, 1.2, 0);
    glTranslatef(-300.0f, 500.0f,0.0f);

    DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Labirinto");
     glPopMatrix();

     glPushMatrix();
     glTranslatef(-60.0f, 480.0f,0.0f);
    glRasterPos2f(-20,-20);
    glColor3f(0.2,0.5,0.1 );
    glScalef(1, 1, 0);
    DesenhaTexto(GLUT_BITMAP_9_BY_15,"Jonas e Matheus");
     glPopMatrix();

    glPushMatrix();
    glColor3f(0.6,0.1,0.9);
    glTranslatef(-950.0f, 450.0f,0.0f);
    glScalef(0.4, 0.4, 0.4);
    glRasterPos2f(-20,-20);

    DesenhaTexto(GLUT_BITMAP_9_BY_15,"Pressione o Botao Esquerdo do Mouse");

     glPopMatrix();

    glPushMatrix();
    glTranslatef(-950.0f, 420.0f,0.0f);
    glScalef(0.4, 0.4, 0.4);
    glRasterPos2f(-20,-20);

    DesenhaTexto(GLUT_BITMAP_9_BY_15,"para abrir o Menu de cores.");
    glPopMatrix();


    glPushMatrix();
    glColor3f(1.0,0.0,0.0);
    sprintf(texto, "Vidas: %d", contVidas-1);
    glTranslatef(1000.0f, 420.0f,0.0f);
    glRasterPos2f(-400,0);
    DesenhaTexto(GLUT_BITMAP_9_BY_15,texto);
    glPopMatrix();


      glPushMatrix();
    glColor3f(0.0,0.0,0.0);
    glTranslatef(350.0f,0.0f,0.0f);
    if(flag == 1){
       strcpy(ganhou, "GANHOU!");
    }else if(flag == 0){
        strcpy(ganhou, "PERDEU!");
    }else{
        strcpy(ganhou, "");
    }
    DesenhaTextoStroke(GLUT_STROKE_ROMAN,ganhou);
     glPopMatrix();

	glFlush();
    glutPostRedisplay();

}


	void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	GLsizei largura, altura;

	if(h == 0) h = 1;
	largura = w;
	altura = h;
	glViewport(0, 0, 1000, 700);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D (-1000, 1000, -700, 700);
}


//fun��o que inicializa as vari�veis antes de desenhar
void Inicializa (void)
{
    colorBack.r = 0.97f;
	colorBack.g = 0.97f;
    colorBack.b=  0.97f;

	glClearColor(colorBack.r, colorBack.g, colorBack.b,1.0f);
	colorQuad.r = 0.1f;
	colorQuad.g = 0.5f;
    colorQuad.b= 0.7f;

    colorLab.r = 0.0f;
	colorLab.g = 0.0f;
    colorLab.b= 0.0f;

    aux.x = 0.0f;
    aux.y = 30.0f;
    vectMisc[0] = aux;

    aux.x = 0.0f;
    aux.y = -30.0f;
    vectMisc[1] = aux;

    aux.x = 800.0f;
    aux.y = 560.0f;
    vectMisc[2] = aux;

    aux.x = 800.0f;
    aux.y = 500.0f;
    vectMisc[3] = aux;

    aux.x = 0.0f;
    aux.y = 30.0f;
    vectLinha1[0] = aux;
    aux.x = 600.0f;
    aux.y = 30.0f;
    vectLinha1[1] = aux;
    aux.x = 600.0f;
    aux.y = 200.0f;
    vectLinha1[2] = aux;
    aux.x = 300.0f;
    aux.y = 200.0f;
    vectLinha1[3] = aux;
    aux.x = 300.0f;
    aux.y = 560.0f;
    vectLinha1[4] = aux;
    aux.x = 430.0f;
    aux.y = 560.0f;
    vectLinha1[5] = aux;
    aux.x = 430.0f;
    aux.y = 500.0f;
    vectLinha1[6] = aux;
    aux.x = 430.0f;
    aux.y = 560.0f;
    vectLinha1[7] = aux;
    aux.x = 550.0f;
    aux.y = 560.0f;
    vectLinha1[8] = aux;
    aux.x = 550.0f;
    aux.y = 500.0f;
    vectLinha1[9] = aux;
    aux.x = 550.0f;
    aux.y = 560.0f;
    vectLinha1[10] = aux;
     aux.x = 670.0f;
    aux.y = 560.0f;
    vectLinha1[11] = aux;
    aux.x = 670.0f;
    aux.y = 500.0f;
    vectLinha1[12] = aux;
    aux.x = 670.0f;
    aux.y = 560.0f;
    vectLinha1[13] = aux;
    aux.x = 840.0f;
    aux.y = 560.0f;
    vectLinha1[14] = aux;
     aux.x = 900.0f;
    aux.y = 560.0f;
    vectLinha1[15] = aux;


    aux.x = 0.0f;
    aux.y = -30.0f;
    vectLinha2[0] = aux;
    aux.x = 660.0f;
    aux.y = -30.0f;
    vectLinha2[1] = aux;
    aux.x = 660.0f;
    aux.y = 260.0f;
    vectLinha2[2] = aux;
    aux.x = 360.0f;
    aux.y = 260.0f;
    vectLinha2[3] = aux;
    aux.x = 360.0f;
    aux.y = 500.0f;
    vectLinha2[4] = aux;
    aux.x = 370.0f;
    aux.y = 500.0f;
    vectLinha2[5] = aux;
    aux.x = 370.0f;
    aux.y = 440.0f;
    vectLinha2[6] = aux;
    aux.x = 490.0f;
    aux.y = 440.0f;
    vectLinha2[7] = aux;
    aux.x = 490.0f;
    aux.y = 500.0f;
    vectLinha2[8] = aux;
     aux.x = 490.0f;
    aux.y = 440.0f;
    vectLinha2[9] = aux;
    aux.x = 610.0f;
    aux.y = 440.0f;
    vectLinha2[10] = aux;
    aux.x = 610.0f;
    aux.y = 500.0f;
    vectLinha2[11] = aux;
     aux.x = 610.0f;
    aux.y = 440.0f;
    vectLinha2[12] = aux;
     aux.x = 730.0f;
    aux.y = 440.0f;
    vectLinha2[13] = aux;
     aux.x = 730.0f;
    aux.y = 500.0f;
    vectLinha2[14] = aux;
     aux.x = 900.0f;
    aux.y = 500.0f;
    vectLinha2[15] = aux;

}

//fun��o do menu da cor do labirinto
void MenuCorLab(int op)
{
   switch(op) {
            case 0:
                     colorLab.r  = 0.0f;
                     colorLab.g  = 0.7f;
                     colorLab.b = 1.0f;
                     break;
            case 1:
                     colorLab.r = 0.3f;
                     colorLab.g = 0.0f;
                     colorLab.b = 0.5f;
                     break;
            case 2:
                     colorLab.r = 0.2f;
                     colorLab.g = 1.0f;
                     colorLab.b = 1.0f;
                     break;
            case 3:
                     colorLab.r = 0.0f;
                     colorLab.g = 0.9f;
                     colorLab.b = 0.1f;
                     break;
            case 4:
                     colorLab.r = 0.4f;
                     colorLab.g = 0.0f;
                     colorLab.b = 0.7f;
                     break;
            case 5:
                     colorLab.r = 1.0f;
                     colorLab.g = 0.1f;
                     colorLab.b = 0.8f;
                     break;
            case 6:
                     colorLab.r = 1.0f;
                     colorLab.g = 0.5f;
                     colorLab.b = 0.1f;
                     break;
            case 7:
                     colorLab.r = 1.0f;
                     colorLab.g = 0.0f;
                     colorLab.b = 0.0f;
                     break;
            case 8:
                     colorLab.r = 1.0f;
                     colorLab.g = 0.9f;
                     colorLab.b = 0.1f;
                     break;
            case 9:
                     colorLab.r = 0.0f;
                     colorLab.g = 0.0f;
                     colorLab.b = 0.0f;
                     break;
    }
    glutPostRedisplay();
}

//fun��o do menu da cor do quadrado
void MenuCor(int op)
{
   switch(op) {
            case 0:
                     colorQuad.r  = 0.0f;
                     colorQuad.g  = 0.7f;
                     colorQuad.b = 1.0f;
                     break;
            case 1:
                     colorQuad.r = 0.3f;
                     colorQuad.g = 0.0f;
                     colorQuad.b = 0.5f;
                     break;
            case 2:
                     colorQuad.r = 0.2f;
                     colorQuad.g = 1.0f;
                     colorQuad.b = 1.0f;
                     break;
            case 3:
                     colorQuad.r = 0.0f;
                     colorQuad.g = 0.9f;
                     colorQuad.b = 0.1f;
                     break;
            case 4:
                     colorQuad.r = 0.4f;
                     colorQuad.g = 0.0f;
                     colorQuad.b = 0.7f;
                     break;
            case 5:
                     colorQuad.r = 1.0f;
                     colorQuad.g = 0.1f;
                     colorQuad.b = 0.8f;
                     break;
            case 6:
                     colorQuad.r = 1.0f;
                     colorQuad.g = 0.5f;
                     colorQuad.b = 0.1f;
                     break;
            case 7:
                     colorQuad.r = 1.0f;
                     colorQuad.g = 0.0f;
                     colorQuad.b = 0.0f;
                     break;
            case 8:
                     colorQuad.r = 1.0f;
                     colorQuad.g = 0.9f;
                     colorQuad.b = 0.1f;
                     break;
            case 9:
                     colorQuad.r = 0.0f;
                     colorQuad.g = 0.0f;
                     colorQuad.b = 0.0f;
                     break;
    }

    glutPostRedisplay();
}

// Gerenciamento do menu com as op��es de cores do fundo
void MenuCorFundo(int op)
{
   switch(op) {
            case 0:
                     colorBack.r  = 0.0f;
                     colorBack.g  = 0.7f;
                     colorBack.b = 1.0f;
                     break;
            case 1:
                     colorBack.r = 0.3f;
                     colorBack.g = 0.0f;
                     colorBack.b = 0.5f;
                     break;
            case 2:
                     colorBack.r = 0.2f;
                     colorBack.g = 1.0f;
                     colorBack.b = 1.0f;
                     break;
            case 3:
                     colorBack.r = 0.0f;
                     colorBack.g = 0.9f;
                     colorBack.b = 0.1f;
                     break;
            case 4:
                     colorBack.r = 0.4f;
                     colorBack.g = 0.0f;
                     colorBack.b = 0.7f;
                     break;
            case 5:
                     colorBack.r = 1.0f;
                     colorBack.g = 0.1f;
                     colorBack.b = 0.8f;
                     break;
            case 6:
                     colorBack.r = 1.0f;
                     colorBack.g = 0.5f;
                     colorBack.b = 0.1f;
                     break;
            case 7:
                     colorBack.r = 1.0f;
                     colorBack.g = 0.0f;
                     colorBack.b = 0.0f;
                     break;
            case 8:
                     colorBack.r = 1.0f;
                     colorBack.g = 0.9f;
                     colorBack.b = 0.1f;
                     break;
            case 9:
                     colorBack.r = 0.0f;
                     colorBack.g = 0.0f;
                     colorBack.b = 0.0f;
                     break;
    }
    glClearColor(colorBack.r, colorBack.g, colorBack.b,1.0f);
    glutPostRedisplay();
}

// Gerenciamento do menu principal
void MenuPrincipal(int op)
{
}

// Criacao do Menu
void CriaMenu()
{
    int menu,submenu1,submenu2, submenu3;

	submenu1 = glutCreateMenu(MenuCor);
	glutAddMenuEntry("Azul Claro",0);
	glutAddMenuEntry("Azul Escuro",1);
	glutAddMenuEntry("Azul Piscina",2);
	glutAddMenuEntry("Verde",3);
	glutAddMenuEntry("Roxo",4);
	glutAddMenuEntry("Rosa",5);
	glutAddMenuEntry("Laranja",6);
	glutAddMenuEntry("Vermelho",7);
	glutAddMenuEntry("Amarelo",8);
	glutAddMenuEntry("Preto",9);

    submenu2 = glutCreateMenu(MenuCorLab);
	glutAddMenuEntry("Azul Claro",0);
	glutAddMenuEntry("Azul Escuro",1);
	glutAddMenuEntry("Azul Piscina",2);
	glutAddMenuEntry("Verde",3);
	glutAddMenuEntry("Roxo",4);
	glutAddMenuEntry("Rosa",5);
	glutAddMenuEntry("Laranja",6);
	glutAddMenuEntry("Vermelho",7);
	glutAddMenuEntry("Amarelo",8);
	glutAddMenuEntry("Preto",9);

    submenu3 = glutCreateMenu(MenuCorFundo);
	glutAddMenuEntry("Azul Claro",0);
	glutAddMenuEntry("Azul Escuro",1);
	glutAddMenuEntry("Azul Piscina",2);
	glutAddMenuEntry("Verde",3);
	glutAddMenuEntry("Roxo",4);
	glutAddMenuEntry("Rosa",5);
	glutAddMenuEntry("Laranja",6);
	glutAddMenuEntry("Vermelho",7);
	glutAddMenuEntry("Amarelo",8);
	glutAddMenuEntry("Preto",9);

    menu = glutCreateMenu(MenuPrincipal);
	glutAddSubMenu("Cor do Quadrado",submenu1);
    glutAddSubMenu("Cor do Labirinto",submenu2);
    glutAddSubMenu("Cor de fundo",submenu3);

	glutAttachMenu(GLUT_LEFT_BUTTON);
}

// Programa Principal
int main(void)
{

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//modo de exibi��o com janela single buffered e padrao de cores rgba
	glutInitWindowPosition(10,10);//posi��o inicial da tela
	glutInitWindowSize(1000,700);//tamanho da tela
	glutCreateWindow("Labirinto");//cria a tela com titulo Labirinto
	glutDisplayFunc(Desenha);//define a fun�ao Desenha como respons�vel por redesenhar a janela OpenGL sempre que necess�rio
	Inicializa();// conven��o do livro pra colocar oq deve ser executado antes de desenhar
	glutReshapeFunc(AlteraTamanhoJanela);//mudar tamannho. N�o usada efetivamente neste codigo
    glutMouseFunc(GerenciaMouse);//
    glutSpecialFunc(TeclasEspeciais);//

    glutMainLoop();//Loop glut

	return 0;

}
