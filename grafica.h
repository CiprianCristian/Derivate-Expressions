#pragma once

#ifndef LIBRARIES_H
#include "libraries.h"
#endif

#include "expression.h"
#include "arbore.h"
#include "deriv.h"

void meniu();
void meniuInformatii();
void meniuDeriv();
void citesteSir(char text[100], char afisare[100], int x, int y, bool stergere);
void citireFunctie(char functieCitita[100]);

void meniu()
{
    initwindow( 1500 , 770, "Deriv" );
    readimagefile("Background.jpg", 0,0,1500,770);
    readimagefile("galben.jpg", 400, 100, 1400, 700);
    readimagefile("InfButton.jpg",75,200,275,260);
    readimagefile("DerivButton.jpg",75,380,275,440);

    jump:
    bool gata = false;
    bool buton1 = false, buton2 = false;
    int x,y;
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x = mousex();
            y = mousey();
            if(x >= 75 && x <= 275 && y >= 200 && y <= 260)
            {
                gata = true;
                buton1 = true;
            }
            else
                if(x >= 75 && x <= 275 && y >= 380 && y <= 440)
                {
                    gata = true;
                    buton2 = true;
                }
        }
    } while (!gata);
     if (buton1 == true)
    {
        meniuInformatii();
        goto jump;
    }
    else
        if (buton2 == true)
        {
            meniuDeriv();
            goto jump;
        }

    getch();
    closegraph();
}

void meniuInformatii()
{
    readimagefile("galben.jpg", 400, 100, 1400, 700);
    setbkcolor(YELLOW);
    setcolor(BLACK);
    settextstyle(8, HORIZ_DIR, 4);
    outtextxy(800 , 120 , "Informatii");
    settextstyle(3, HORIZ_DIR, 2);
    outtextxy( 480 , 170 , "Programul va efectua derivata de ordinul I si de ordinul al II - lea de o singura variabila care va fi x.");
    outtextxy( 480 , 200 , "Orice functie care nu va fi dependenta de x va fi considerata ca si o constanta.");
    outtextxy( 480 , 250 , "Se vor utiliza functii care contin:");
    outtextxy( 480 , 280 , "        Operatori binari: + - * / ^ ");
    outtextxy( 480 , 310 , "        Operatori unari: sin() cos() tg() ctg() sqrt() log() ");
    outtextxy( 480 , 370 , "Pentru a deriva ''radical de ordin n din x'' se va scrie  sqrtn(x)");
    outtextxy( 480 , 400 , "Pentru a deriva ''logaritm in baza n din x'' se va scrie  logn(x)");
    outtextxy( 480 , 430 , "In cazul in care nu se va mentiona nicio baza / ordin se va pune automat baza / ordinul 2");
}

void meniuDeriv()
{
    readimagefile("galben.jpg", 400, 100, 1400, 700);
    setbkcolor(YELLOW);
    setcolor(BLACK);
    settextstyle(8, HORIZ_DIR, 4);
    outtextxy(800 , 120 , "Deriveaza");
    char functieCitita[100];
    citireFunctie(functieCitita);
    settextstyle(3 , HORIZ_DIR , 2 );

    unsigned int success;
    string expresie = functieCitita;

    tokenVector infix;
	tokenize(infix, expresie, success);

	if (!success)
        {
            setcolor(RED);
            settextstyle( 1 , HORIZ_DIR , 5 );
            outtextxy( 800 , 350 , "EROARE");
            return ;
        }

    tokenVector postfix;
	postfixize(infix, postfix);

	ExpTree tree = NULL;
	tree = constructTree(tree, postfix);

	ExpTree derivTree = new TreeNode;
    ExpTree derivTree2 = new TreeNode;

    string afisFunctie , afisFunctie2;

	deriveaza(tree, derivTree);
	tree = derivTree;
	simplifica(tree);
    afiseaza( tree , afisFunctie );

    char functieDerivata[afisFunctie.length()+1];
    strcpy( functieDerivata , afisFunctie.c_str() );

    outtextxy( 480 , 250 , "Derivata de ordin I este: ");

    unsigned int x = 680 , y = 250 , i = 0;

   if( strlen(functieDerivata) > 75 )
   {
        while( i<strlen(functieDerivata) )
        {
            if(x>1300) {x=680; y = y + 25;}
            bgiout<<functieDerivata[i];
            i++;
            outstreamxy( x , y );
            x+=10;
        }
   }
   else
    {
      bgiout<<functieDerivata;
      outstreamxy(680,250);
    }

    deriveaza( derivTree, derivTree2 );
    simplifica2( derivTree2 );
    afiseaza( derivTree2 , afisFunctie2 );

    char functieDerivata2[afisFunctie2.length()+1];
    strcpy( functieDerivata2 , afisFunctie2.c_str() );

    outtextxy( 480 , 400 , "Derivata de ordin II este: ");

    x = 680 , y = 400 , i = 0;

    if( strlen(functieDerivata2) > 75 )
   {
        while( i<strlen(functieDerivata2) )
        {
            if(x>1300) {x=680; y = y + 25;}
            bgiout<<functieDerivata2[i];
            i++;
            outstreamxy( x , y );
            x+=10;
        }
   }
   else
    {
      bgiout<<functieDerivata2;
      outstreamxy(680,400);
    }
}

void citesteSir(char text[100], char afisare[100], int x, int y, bool stergere)
{
    strcpy(afisare, "");
    char aux[100];
    char key[2];  // sirul in care se pastreaza tasta pe care o apasam la citire
    char tasta;   // tasta pe care se apasa
    char text2[100];
    key[0] = tasta;
    key[1] = '\0';
    strcat(afisare, key);
    strcpy(aux, afisare);
    strcat(aux, "_");
    setcolor(BLACK);
    setbkcolor(YELLOW);
    strcpy(text2, text);
    strcat(text2, aux);
    outtextxy(x, y, text2);
    do
    {
        tasta = getch();
        if (tasta == 8) // backspace
            if (strlen(afisare) > 0)
            {
                setcolor(YELLOW);
                strcpy(aux, afisare);
                strcat(aux, "_");
                strcpy(text2, text);
                strcat(text2, aux);
                outtextxy(x, y, text2);
                afisare[strlen(afisare) - 1] = '\0';
                strcpy(aux, afisare);
                strcat(aux, "_");
                strcpy(text2, text);
                strcat(text2, aux);
                outtextxy(x, y, text2);
                setcolor(BLACK);
                strcpy(text2, text);
                strcat(text2, aux);
                outtextxy(x, y, text2);
            }
            else
                Beep(1000,100);
        else
        {
            key[0] = tasta;
            key[1] = '\0';
            strcat(afisare, key);
            strcpy(aux, afisare);
            strcat(aux, "_");
            setcolor(BLACK);
            strcpy(text2, text);
            strcat(text2, aux);
            outtextxy(x, y, text2);
        }
    } while (tasta!=13);

    key[0] = tasta;
    key[1] = '\0';
    strcat(afisare, key);
    strcpy(aux, afisare);
    strcat(aux, "_");
    strcpy(text2, text);
    strcat(text2, aux);

    setcolor(BLACK);
    outtextxy(x,y,text2);

    if (!stergere)
    {
        strcpy(text2,text);
        strcat(text2,afisare);
        setcolor(BLACK);
        outtextxy(x,y,text2);
    }
}

void citireFunctie(char functieCitita[100])
{
    settextstyle(3, HORIZ_DIR, 2);
    setbkcolor(YELLOW);
    setcolor(BLACK);
    citesteSir("Introduceti functia: ", functieCitita, 480, 170, false);
    setbkcolor(YELLOW);
    setcolor(BLACK);
}
