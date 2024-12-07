#include <stdio.h>

void erstelleNullBoard(int uebergebenesBoard[9][9])
{
    for (int i = 0; i < 9; i++) // Schleife über alle Zeilen
    {
        for (int j = 0; j < 9; j++) // Schleife über alle Spalten
        {
            uebergebenesBoard[i][j] = 0; // Setze jedes Element des Boards auf 0
        }
    }
}

void printBoard(int uebergebenesBoard[9][9])
{
    for (int i = 0; i < 9; i++) // Schleife über die Zeilen
    {
        // Trennlinie nach jeder dritten Zeile
        if (i % 3 == 0)
        {
            printf("+-------+-------+-------+\n");
        }

        for (int j = 0; j < 9; j++) // Schleife über die Spalten
        {
            if (j % 3 == 0) // Zusätzliche Trennlinie vor jeder dritten Spalte
            {
                printf("| ");
            }

            printf("%d ", uebergebenesBoard[i][j]); // Druckt das aktuelle Board-Element

            // Am Ende der Zeile (bei der 9. Spalte): abschließendes '|'
            if (j == 8)
            {
                printf("|");
            }
        }
        printf("\n"); 
    }

    printf("+-------+-------+-------+\n");
}

int check_double_felder(int uebergebenesBoard[9][9], int zeile, int spalte, int wert)
{
    // Durch Division der Zeile und Spalte durch 3 und Multiplikation mit 3 wird die obere linke Ecke des Blocks ermittelt.
    int feld_start_zeile = (zeile / 3) * 3; 
    int feld_start_spalte = (spalte / 3) * 3; 

    for (int i = 0; i < 3; i++) // Iteriert über die 3 Zeilen des Blocks
    {
        for (int j = 0; j < 3; j++) // Iteriert über die 3 Spalten des Blocks
        {
           
            if (uebergebenesBoard[feld_start_zeile + i][feld_start_spalte + j] == wert)  // Prüft, ob die Zahl `wert` bereits in einer der Zellen des Blocks vorhanden ist
            {
              
                printf("Die Zahl %d ist bereits in diesem Feldblock vorhanden.\n", wert);
                return 1; 
            }
        }
    }

    // Wenn die Zahl in keinem der Felder gefunden wurde, ist sie zulässig
    return 0; 
}


int check_double_zeilen_spalten(int uebergebenesBoard[9][9], int zeile, int spalte, int wert)
{
    int i; 

    // Prüft ob im Array zeilen_elemente die Zahl vorkommt  
    // oder ob im Array spalten_elemente die Zahl vorkommt
    for (i = 0; i < 9; i++)
    {   
        
        if (uebergebenesBoard[zeile - 1][i] == wert)
        {
            printf("Die Zahl %d ist bereits in Zeile %d und Spalte %d vorhanden.\n", wert, zeile, i + 1);
            return 1;
        }
        else if (uebergebenesBoard[i][spalte - 1] == wert)
        {
            printf("Die Zahl %d ist bereits in Zeile %d und Spalte %d vorhanden.\n", wert, i + 1, spalte);
            return 1;
        }
    }

    return 0; 
}

int check_if_occupied(int uebergebenesBoard[9][9], int zeile, int spalte)
{
     // Prüft ob die Position bereits belegt ist
    if(uebergebenesBoard[zeile - 1][spalte - 1] == 0)
    {
        return 0; 
    }
    else
    {
        printf("Diese Position ist bereits besetzt. Bitte wählen Sie eine andere Position.\n");
        return 1;
    }
    
}

void set_board_element(int uebergebenesBoard[9][9])
{   
    int zeile, spalte, wert; 
    char ende;

    
    Start:
    // Eingabe Zeile
    while(1)
    {
        printf("In welcher Zeile wollen Sie die Zahl setzen (1 bis 9)? ");
         
        if (scanf("%d%c", &zeile, &ende) == 2 && // Prüft ob Buchstabe oder nicht,
           (ende == '\n' || ende == ' ') && // &ende prüft ob ganze Zahl oder nicht
           (zeile >= 1 && zeile <= 9)) // Prüft, ob die Zeile zwischen 1 und 9 liegt
        {
            break;
        }
        else 
        {
            printf("Falsche Eingabe. Bitte geben Sie eine Zahl zwischen 1 und 9 ein.\n");
            while (getchar() != '\n'); // Entfernt restliche Zeichen aus dem Puffer
        }

    }

    // Eingabe Spalte
    while(1)
    {
        printf("In welcher Spalte wollen Sie die Zahl setzen (1 bis 9)? ");
        
        if (scanf("%d%c", &spalte, &ende) == 2 && // Prüft ob Buchstabe oder nicht
           (ende == '\n' || ende == ' ')  && // &ende prüft ob ganze Zahl oder nicht
           (spalte >= 1 && spalte <= 9)) // Prüfe, ob die Eingabe eine ganze Zahl ist
        {
            break;
        }
        else 
        {
            printf("Falsche Eingabe. Bitte geben Sie eine Zahl zwischen 1 und 9 ein.\n");
            while (getchar() != '\n'); // Entfernt restliche Zeichen aus dem Puffer
        }
    }

    if (check_if_occupied(uebergebenesBoard, zeile, spalte) == 1)
    {
        goto Start;
    }
   
    // Eingabe Zahl
    while(1)
    {
        printf("Welche Zahl moechten Sie einsetzen? (1 bis 9)? ");
        //&ende prüft ob ganze Zahl oder nicht
        if (scanf("%d%c", &wert, &ende) == 2 && // Prüft ob Buchstabe oder nicht
            (ende == '\n' || ende == ' ') && // &ende prüft ob ganze Zahl oder nicht
            (wert >= 1 && wert <= 9)) // Prüfe, ob die Eingabe eine ganze Zahl ist
        {
            break;
        }
        else 
        {
            printf("Falsche Eingabe. Bitte geben Sie eine Zahl zwischen 1 und 9 ein.\n");
            while (getchar() != '\n'); // Entfernt restliche Zeichen aus dem Puffer
        }
    }

    // Addiert alle return Werte der Funktionen
    int wahrheitswert = check_double_zeilen_spalten(uebergebenesBoard, zeile, spalte, wert) + check_double_felder(uebergebenesBoard, zeile, spalte, wert);
  
    // wenn 0, dann ist die Eingabe gültig
    if (wahrheitswert == 0)
    {
        saveBoardState(uebergebenesBoard);
        uebergebenesBoard[zeile - 1][spalte - 1] = wert; // Setzt die Zahl in das Board
    }

    


}

int solve(int uebergebenesBoard[9][9], int zeile, int spalte) 
{
    int wert; 
    
    if (zeile == 9) // Wenn alle Zeilen abgearbeitet sind, ist das Sudoku vollständig gelöst
    {
        return 1; 
    }
    else if (spalte == 9)  // Wenn alle Spalten in der aktuellen Zeile abgearbeitet sind, springt zur nächsten Zeile
    {
        return solve(uebergebenesBoard, zeile + 1, 0); // Wechselt zur nächsten Zeile und starte bei Spalte 0
    }
    else if (uebergebenesBoard[zeile][spalte] != 0)    // Wenn die aktuelle Zelle bereits einen festen Wert hat, wird übersprungen
    {
        return solve(uebergebenesBoard, zeile, spalte + 1); 
    }
    else 
    {
        for (wert = 1; wert < 10; wert++) //geht alle Werte von 1 bis 9 durch
        {
            if (check_double_zeilen_spalten(uebergebenesBoard, zeile + 1, spalte + 1, wert) == 0 &&  // Prüft, ob der Wert in der aktuellen Zeile, Spalte oder dem 3x3-Block gültig ist
                check_double_felder(uebergebenesBoard, zeile, spalte, wert) == 0) 
            {
                saveBoardState(uebergebenesBoard); // Speichert den aktuellen Zustand des Boards (für "Undo"-Funktion
                
                uebergebenesBoard[zeile][spalte] = wert;  // Setzt den Wert in das Board

                if (solve(uebergebenesBoard, zeile, spalte + 1) == 1) // Prüft, ob das Sudoku mit diesem Wert lösbar ist
                {
                    return 1; // Sudoku erfolgreich gelöst 
                }

                uebergebenesBoard[zeile][spalte] = 0; // Rückgängigmachen der Änderung (Backtracking), wenn der aktuelle Wert nicht zur Lösung führt
            }
        }

        return 0;
    }
}


void open_file(FILE **datei, char *dateiname) 
{
    // Versucht, die Datei im Lese-Modus ("rt" für Read Text) zu öffnen
    
    if ((*datei = fopen(dateiname, "rt")) == NULL) // Der Dateizeiger wird auf die Datei gesetzt, falls das Öffnen erfolgreich ist
    {
        printf("Datei %s konnte nicht geoeffnet werden\n", dateiname);
    }
    else 
    {
        printf("Datei %s konnte geoeffnet werden.\n", dateiname);
    }
}


void load_file(FILE *datei, int uebergebenesBoard[9][9])
{
    int k = 0;
    int i, j, c;
    int eingelesenes_sudokufeld_1d_array[81] = {}; // Array zur Speicherung der Sudoku-Zahlen als 1D-Array

   
    while((c = fgetc(datei)) != EOF)  // Liest die Datei Zeichen für Zeichen, bis das Ende der Datei erreicht ist
    {
       
        if(isdigit(c))  // Wenn das gelesene Zeichen eine Zahl ist
        {
            
            eingelesenes_sudokufeld_1d_array[k] = c - '0'; // Umwandlung von ASCII-Zeichen in Integer (Ziffer) und Speicherung im 1D-Array
            k++;  // Erhöht den Index für das nächste Feld
        }
    }

    
    for(i = 0; i < 9; i++) // Konvertiert das 1D-Array in ein 2D-Array (Sudoku-Board)
    {
        for(j = 0; j < 9; j++) 
        {
            uebergebenesBoard[i][j] = eingelesenes_sudokufeld_1d_array[i * 9 + j]; 
        }
    }

    printf("\n"); 
}


void close_file(FILE *datei, char *dateiname)
{
    
    if(fclose(datei) == 0) // Versucht, die Datei zu schließen + Fehlermeldung ausgeben
    {
        printf("Datei %s geschlossen.\n", dateiname);
    }
    else 
    {
        printf("Datei %s konnte nicht geschlossen werden.\n", dateiname);
    }
}




#define MAX_UNDO 100 // Maximale Anzahl der Zustände, die gespeichert werden können
typedef struct 
{
    int board[9][9]; // Zustand des Sudoku-Boards
} BoardState;

BoardState undoStack[MAX_UNDO]; // Stack zur Speicherung von Zuständen
int undoIndex = -1; // Last-in-first-out, Zeiger auf die aktuelle Position im Stack

void saveBoardState(int uebergebenesBoard[9][9]) {
  
    if (undoIndex < MAX_UNDO - 1)   // Überprüft, ob der Undo-Stack noch Platz hat (maximale Anzahl an Undo-Schritten ist MAX_UNDO)
    {
        undoIndex++;  // Erhöht den Index für die nächste Speicherstelle im Undo-Stack
        
        // Kopiere das aktuelle Sudoku-Board in den Undo-Stack an der Position undoIndex
        for (int i = 0; i < 9; i++) 
        {
            for (int j = 0; j < 9; j++) 
            {
                undoStack[undoIndex].board[i][j] = uebergebenesBoard[i][j]; // Speichere jedes Feld des Boards
            }
        }
    } 
    else 
    {
        printf("Undo-Speicher ist voll!\n");
    }
}


void undo(int uebergebenesBoard[9][9]) {
    if (undoIndex >= 0) // Wenn gespeicherte Zustände vorhanden, bei undoIndex = -1 keine Speicherzustände vorhanden
    {
        for (int i = 0; i < 9; i++) 
        {
            for (int j = 0; j < 9; j++) 
            {
                uebergebenesBoard[i][j] = undoStack[undoIndex].board[i][j];
            }
        }
        undoIndex--; // Zum vorherigen Zustand wechseln
    } 
    else 
    {
        printf("Keine weiteren Undo-Schritte verfügbar!\n");
    }
}

int speichern(int uebergebenesBoard[9][9], char *dateiname) 
{
    FILE *fp; // Zeiger auf die Datei
    int i, j; // Variablen für die Schleifen

    // Datei zum Schreiben öffnen ("w" steht für Write-Modus) + Fehlermeldung ausgeben
    if ((fp = fopen(dateiname, "w")) == NULL) 
    {
        printf("Die Datei %s konnte nicht geöffnet werden.\n", dateiname);
        return 1; 
    }

 
    for (i = 0; i < 9; i++) // Iteriert über alle Zeilen
    {
        for (j = 0; j < 9; j++) // Iteriert über alle Spalten
        {
            // Schreibt den aktuellen Wert ins File
            fprintf(fp, "%d ", uebergebenesBoard[i][j]);
        }
        fprintf(fp, "\n"); 
    }

    if (fclose(fp) == 0) 
    {
        printf("Die Datei %s wurde erfolgreich gespeichert.\n", dateiname);
    } 
    else 
    {
        printf("Die Datei %s konnte nicht geschlossen werden.\n", dateiname);
        return 1; 
    }

    return 0; // Rückgabe von 0 signalisiert, dass alles erfolgreich war
}
