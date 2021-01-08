#pragma once

#ifndef LIBRARIES_H
#include "libraries.h"
#endif

#include "arbore.h"

void deriveaza(ExpTree& arbi, ExpTree& arbd)
{
    if (arbi == NULL)
        return;

    ExpTree arb1, arb2, arb3, arb4, arb5, arb6, arb7;
    arb1 = new TreeNode;
    arb2 = new TreeNode;
    arb3 = new TreeNode;
    arb4 = new TreeNode;
    arb5 = new TreeNode;
    arb6 = new TreeNode;
    arb7 = new TreeNode;

    if (arbi->info == "x")
    {
        arbd->left = NULL;
        arbd->right = NULL;
        arbd->info = "1";
    }
    else if (arbi->info == "+")
    {
        deriveaza(arbi->left, arb1);
        arbd->left = arb1;
        deriveaza(arbi->right, arb2);
        arbd->right = arb2;
        arbd->info = "+";
    }
    else if (arbi->info == "-")
    {
        deriveaza(arbi->left, arb1);
        arbd->left = arb1;
        deriveaza(arbi->right, arb2);
        arbd->right = arb2;
        arbd->info = "-";
    }
    else if (arbi->info == "*")
    {
        deriveaza(arbi->left, arb3);
        deriveaza(arbi->right, arb4);
        arbd->info = "+";
        arb1->left = arb3;
        arb1->right = arbi->right;
        arb1->info = "*";
        arb2->left = arbi->left;
        arb2->right = arb4;
        arb2->info = "*";
        arbd->left = arb1;
        arbd->right = arb2;
    }
    else if (arbi->info == "/")
    {
        deriveaza(arbi->left, arb3);
        deriveaza(arbi->right, arb4);
        arb2->info = "*";
        arb1->left = arb3;
        arb1->right = arbi->right;
        arb1->info = "*";
        arb2->left = arbi->left;
        arb2->right = arb4;
        arb5->info = "-";
        arb5->left = arb2;
        arb5->right = arb1;
        arb6->info = "2";
        arb6->left = NULL;
        arb6->right = NULL;
        arb7->info = "^";
        arb7->left = arbi->right;
        arb7->right = arb6;
        arbd->info = "/";
        arbd->left = arb5;
        arbd->right = arb7;
    }
    else if (arbi->info == "sin")
    {
        arb1->info = "cos";
        arb1->right = arbi->right;
        arb1->left = NULL;
        deriveaza(arbi->right, arb2);
        arbd->info = "*";
        arbd->left = arb1;
        arbd->right = arb2;
    }
    else if (arbi->info == "cos")
    {
        deriveaza(arbi->right, arb4);
        arb1->info = "0";
        arb1->left = NULL;
        arb1->right = NULL;
        arb2->info = "sin";
        arb2->right = arbi->right;
        arb2->left = NULL;
        arb3->info = "*";
        arb3->left = arb2;
        arb3->right = arb4;
        arbd->info = "-";
        arbd->left = arb1;
        arbd->right = arb3;
    }
    else if (arbi->info == "tg")
    {
        deriveaza(arbi->right, arb1);
        arb3->info = "cos";
        arb3->right = arbi->right;
        arb3->left = NULL;
        arb4->info = "2";
        arb4->left = NULL;
        arb4->right = NULL;
        arb2->info = "^";
        arb2->left = arb3;
        arb2->right = arb4;
        arbd->info = "/";
        arbd->left = arb1;
        arbd->right = arb2;
    }
    else if (arbi->info == "ctg")
    {
        deriveaza(arbi->right, arb1);
        arb4->info = "sin";
        arb4->right = arbi->right;
        arb4->left = NULL;
        arb5->info = "2";
        arb5->left = NULL;
        arb5->right = NULL;
        arb3->info = "^";
        arb3->left = arb4;
        arb3->right = arb5;
        arb2->info = "/";
        arb2->left = arb1;
        arb2->right = arb3;
        arb6->info = "0";
        arb6->left = NULL;
        arb6->right = NULL;
        arbd->info = "-";
        arbd->left = arb6;
        arbd->right = arb2;
    }
    else if (arbi->info == "^")
    {
        deriveaza(arbi->left, arb1);
        arb5->info = "1";
        arb5->left = NULL;
        arb5->right = NULL;
        arb2->info = "-";
        arb2->left = arbi->right;
        arb2->right = arb5;
        arb3->info = "^";
        arb3->left = arbi->left;
        arb3->right = arb2;
        arb4->info = "*";
        arb4->left = arbi->right;
        arb4->right = arb3;
        arbd->info = "*";
        arbd->left = arb4;
        arbd->right = arb1;
    }
    else if (arbi->info == "sqrt")
    {
        deriveaza(arbi->right, arb1);
        int coefR = stoi(arbi->coef);
        arb6->right = NULL;
        arb6->left = NULL;
        arb6->info = to_string(coefR - 1);
        arb5->info = "^";
        arb5->left = arbi->right;
        arb5->right = arb6;
        arb4->info = "sqrt";
        arb4->coef = arbi->coef;
        arb4->left = NULL;
        arb4->right = arb5;
        arb3->info = arbi->coef;
        arb3->left = NULL;
        arb3->right = NULL;
        arb2->info = "*";
        arb2->left = arb3;
        arb2->right = arb4;
        arbd->left = arb1;
        arbd->right = arb2;
        arbd->info = "/";
    }
    else if (arbi->info == "log" && arbi->coef == "e")
    {
        deriveaza(arbi->right, arb1);

        arbd->info = "/";
        arbd->left = arb1;
        arbd->right = arbi->right;
    }
    else if (arbi->info == "log")
    {
        deriveaza(arbi->right, arb1);

        arb3->info = "ln" + arbi->coef;
        arb3->left = NULL;
        arb3->right = NULL;
        arb2->info = "*";
        arb2->left = arbi->right;
        arb2->right = arb3;
        arbd->info = "/";
        arbd->left = arb1;
        arbd->right = arb2;
    }
    else
    {
        arbd->info = "0";
        arbd->left = NULL;
        arbd->right = NULL;
    }
}
void afiseaza(ExpTree& arb)
{
    if (arb == NULL)
        return;

    if (arb->info == "sin" || arb->info == "cos" || arb->info == "tg" || arb->info == "ctg")
    {
        cout << arb->info << '(';
        afiseaza(arb->right);
        cout << ')';
    }
    else if (arb->info == "log")
    {
        cout << arb->info << arb->coef << '(';;
        afiseaza(arb->right);
        cout << ')';
    }
    else if (arb->info == "sqrt")
    {
        cout << arb->info << arb->coef << '(';;
        afiseaza(arb->right);
        cout << ')';
    }
    else if (arb->info == "-" || arb->info == "*" || arb->info == "/" || arb->info == "^")
    {
        ExpTree fiuStang, fiuDrept;
        fiuStang = new TreeNode;
        fiuDrept = new TreeNode;
        fiuStang = arb->left;
        fiuDrept = arb->right;

        if (fiuStang != NULL)
        {
            if ((fiuStang->left == NULL && fiuStang->right == NULL) || fiuStang->info == "sin" || fiuStang->info == "cos" || fiuStang->info == "tg" || fiuStang->info == "ctg")
                afiseaza(fiuStang);
            else
            {
                cout << '(';
                afiseaza(arb->left);
                cout << ')';
            }
        }
        cout << arb->info;

        if (fiuDrept != NULL)
        {
            if ((fiuDrept->left == NULL && fiuDrept->right == NULL) || fiuDrept->info == "sin" || fiuDrept->info == "cos" || fiuDrept->info == "tg" || fiuDrept->info == "ctg")
                afiseaza(arb->right);
            else
            {
                cout << '(';
                afiseaza(arb->right);
                cout << ')';
            }
        }
    }
    else
    {
        afiseaza(arb->left);
        cout << arb->info;
        afiseaza(arb->right);
    }
}
void simplifica(ExpTree& arb)
{
    if (arb->info == "sin" || arb->info == "cos" || arb->info == "tg" || arb->info == "ctg" || arb->info == "sqrt" || arb->info == "log")
    {
        simplifica(arb->right);
        return;
    }

    if (arb == NULL || (arb->left == NULL && arb->right == NULL))
        return;

    simplifica(arb->left);
    simplifica(arb->right);

    ExpTree arbST, arbDR;
    arbST = new TreeNode;
    arbDR = new TreeNode;
    arbST = arb->left;
    arbDR = arb->right;

    if (arbST->info[0] >= '0' && arbST->info[0] <= '9' && arbDR->info[0] >= '0' && arbDR->info[0] <= '9')
    {
        int numarST, numarDR, numarNOU;
        numarST = stoi(arbST->info);
        numarDR = stoi(arbDR->info);

        if (arb->info == "+")
        {
            numarNOU = numarST + numarDR;
            arb->info = to_string(numarNOU);
            arb->left = NULL;
            arb->right = NULL;
        }
        else if (arb->info == "-")
        {
            numarNOU = numarST - numarDR;
            arb->info = to_string(numarNOU);
            arb->left = NULL;
            arb->right = NULL;
        }
        else if (arb->info == "*")
        {
            numarNOU = numarST * numarDR;
            arb->info = to_string(numarNOU);
            arb->left = NULL;
            arb->right = NULL;
        }
        else if (arb->info == "/")
        {
            numarNOU = numarST / numarDR;
            arb->info = to_string(numarNOU);
            arb->left = NULL;
            arb->right = NULL;
        }
    }
    else if (arb->info == "+")
    {
        if (arbST->info == "0")
            arb = arbDR;
        else if (arbDR->info[0] == '0')
            arb = arbST;
    }
    else if (arb->info == "-")
    {
        if (arbST->info == "0")
            arb->left = NULL;

        if (arbDR->info == "0")
            arb = arbST;
    }
    else if (arb->info == "*")
    {
        if (arbST->info == "0" || arbDR->info == "0")
        {
            arb->info = "0";
            arb->left = NULL;
            arb->right = NULL;
        }
        else if (arbST->info == "1")
            arb = arbDR;
        else if (arbDR->info == "1")
            arb = arbST;
    }
    else if (arb->info == "/")
    {
        if (arbST->info == "0")
        {
            arb->info = "0";
            arb->left = NULL;
            arb->right = NULL;
        }
        else if (arbDR->info == "1")
            arb = arbST;
    }
    else if (arb->info == "^")
    {
        if (arbDR->info == "1")
            arb = arbST;
        else if (arbST->info == "1" || arbDR->info == "0")
        {
            arb->left = NULL;
            arb->right = NULL;
            arb->info = "1";
        }
        else if (arbST->info == "0")
        {
            arb->left = NULL;
            arb->right = NULL;
            arb->info = "0";
        }
    }
}