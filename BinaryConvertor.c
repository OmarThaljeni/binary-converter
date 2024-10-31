#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Copyright (c) 2024 Intissar Oukhai
 * All rights reserved.
 * *
 * Description: This program converts between decimal, binary, octal, and hexadecimal representations.
 */

void inverserChaine(char*);
char* decimalVersBinaire(int decimal);
int binaireVersDecimal(char binaire[]);
char* decimalVersOctal(int decimal);
int octalVersDecimal(char octal[]);
char* hexadecimalVersBinaire(char hex[]);
char* binaireVersHexadecimal(char binaire[]);
void afficherBinaireAvecEtoiles(char* binaire);

void inverserChaine(char* str) {
    int i = 0;
    int j = strlen(str) - 1;
    while (i < j) {
        char c = str[i];
        str[i] = str[j];
        str[j] = c;
        i++;
        j--;
    }
}

char* decimalVersBinaire(int decimal) {
    char* binaire = (char*)malloc(33);
    if (!binaire) {
        printf("Échec de l'allocation mémoire.\n");
        exit(1);
    }

    int i = 0;
    while (decimal) {
        binaire[i++] = '0' + (decimal & 1);
        decimal >>= 1;
    }
    binaire[i] = '\0';
    inverserChaine(binaire);
    return binaire;
}

int binaireVersDecimal(char binaire[]) {
    int decimal = 0;
    int longueur = strlen(binaire);
    for (int i = 0; i < longueur; i++) {
        decimal = decimal * 2 + (binaire[i] - '0');
    }
    return decimal;
}

char* decimalVersOctal(int decimal) {
    char* octal = (char*)malloc(12);
    if (!octal) {
        printf("Échec de l'allocation mémoire.\n");
        exit(1);
    }
    sprintf(octal, "%o", decimal);
    return octal;
}

int octalVersDecimal(char octal[]) {
    int decimal = 0;
    int longueur = strlen(octal);
    for (int i = 0; i < longueur; i++) {
        decimal = decimal * 8 + (octal[i] - '0');
    }
    return decimal;
}

char* hexadecimalVersBinaire(char hex[]) {
    unsigned int hexNum;
    sscanf(hex, "%x", &hexNum);
    char binaire[33] = "";
    int i = 0;
    while (hexNum) {
        binaire[i++] = '0' + hexNum % 2;
        hexNum /= 2;
    }
    binaire[i] = '\0';
    inverserChaine(binaire);
    return strdup(binaire);
}

char* binaireVersHexadecimal(char binaire[]) {
    int longueur = strlen(binaire);
    int padding = (4 - (longueur % 4)) % 4;
    char binairePadded[129];
    memset(binairePadded, '0', padding);
    strcpy(binairePadded + padding, binaire);
    
    char* chiffresHexa[] = { 
        "0000", "0001", "0010", "0011", 
        "0100", "0101", "0110", "0111", 
        "1000", "1001", "1010", "1011", 
        "1100", "1101", "1110", "1111" 
    };
    
    char hexadecimal[33] = ""; 
    
    for (int i = 0; i < longueur + padding; i += 4) {
        char groupe[5];
        strncpy(groupe, binairePadded + i, 4);
        groupe[4] = '\0';

        for (int j = 0; j < 16; j++) {
            if (strcmp(groupe, chiffresHexa[j]) == 0) {
                char chiffreHexa[2];
                sprintf(chiffreHexa, "%X", j);
                strcat(hexadecimal, chiffreHexa);
                break;
            }
        }
    }
    return strdup(hexadecimal);
}

void afficherBinaireAvecEtoiles(char* binaire) {
    printf("Représentation binaire avec étoiles: ");
    for (int i = 0; binaire[i] != '\0'; i++) {
        if (binaire[i] == '1') {
            printf("* ");
        } else {
            printf("- ");
        }
    }
    printf("\n");
}

int main() {
    int choix;
    while (1) {
printf("Bienvenue dans le convertisseur binaire d'Intissar:\n");
        printf("1. Décimal à Binaire\n");
        printf("2. Binaire à Décimal\n");
        printf("3. Décimal à Octal\n");
        printf("4. Octal à Décimal\n");
        printf("5. Hexadécimal à Binaire\n");
        printf("6. Binaire à Hexadécimal\n");
        printf("7. Événement Binaire (afficher avec étoiles)\n");
        printf("8. Quitter\n");
        printf("Entrez votre choix: ");
        
        if (scanf("%d", &choix) != 1) {
            printf("Entrée invalide. Veuillez entrer un nombre.\n");
            while (getchar() != '\n');
            continue;
        }

        if (choix == 8) {
            printf("Au revoir!\n");
            break;
        }

        char input[100]; 
        switch (choix) {
        case 1:
            printf("Entrez un nombre décimal: ");
            int dec1;
            if (scanf("%d", &dec1) != 1) {
                printf("Entrée invalide. Veuillez entrer un nombre.\n");
                while (getchar() != '\n');
                break;
            }
            char* resultat = decimalVersBinaire(dec1);
            printf("Décimal à Binaire: %s\n", resultat);
            free(resultat);
            break;
        case 2:
            printf("Entrez un nombre binaire: ");
            scanf("%s", input);
            int binaireResultat = binaireVersDecimal(input);
            printf("Binaire à Décimal: %d\n", binaireResultat);
            break;
        case 3:
            printf("Entrez un nombre décimal: ");
            int dec2;
            if (scanf("%d", &dec2) != 1) {
                printf("Entrée invalide. Veuillez entrer un nombre.\n");
                while (getchar() != '\n');
                break;
            }
            resultat = decimalVersOctal(dec2);
            printf("Décimal à Octal: %s\n", resultat);
            free(resultat);
            break;
        case 4:
            printf("Entrez un nombre octal: ");
            scanf("%s", input);
            int octalResultat = octalVersDecimal(input);
            printf("Octal à Décimal: %d\n", octalResultat);
            break;
        case 5:
            printf("Entrez un nombre hexadécimal: ");
            scanf("%s", input);
            resultat = hexadecimalVersBinaire(input);
            printf("Hexadécimal à Binaire: %s\n", resultat);
            free(resultat);
            break;
        case 6:
            printf("Entrez un nombre binaire: ");
            scanf("%s", input);
            resultat = binaireVersHexadecimal(input);
            printf("Binaire à Hexadécimal: %s\n", resultat);
            free(resultat);
            break;
        default:
            printf("Choix invalide. Veuillez entrer une option valide.\n");
        }
    }

    return 0;
}