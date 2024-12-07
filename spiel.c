#include <stdio.h>
#include "sudoku.c" // Enthält Funktionen für das Laden, Speichern und Bearbeiten des Sudoku-Boards

int main()
{
    // Umlaute und Sonderzeichen in der Konsole anzeigen
    system("chcp 65001 > NUL");

    // Dateizeiger und Dateinamen für verschiedene Schwierigkeitsgrade definieren
    FILE *fp;
    char easy[50] = "easy.txt";   // Datei für einfaches Sudoku
    char medium[50] = "medium.txt"; // Datei für mittleres Sudoku
    char hard[50] = "hard.txt";   // Datei für schweres Sudoku

    char dateiname[50] = "data.txt"; 
    int board[9][9];                
    int e;                           // Variable für Benutzereingabe im Menü
    int running = 1;                 // Kontrollvariable, um die Hauptschleife zu steuern
    int continuePlaying;             // Variable, um das Weiterspielen im Spielmodus zu steuern


    printf("WiLLKOMMEN ZUM SUDOKU\n");
    printf("-----------------------\n");
         
    // Hauptschleife des Programms, die so lange läuft, bis der Benutzer das Spiel beendet
    while(running)
    {
    
        printf("Menue:\n");
        printf(" 1 - Datei laden\n 2 - Spiel anzeigen\n 3 - Spiel spielen\n 4 - Rückgängig machen\n");
        printf(" 5 - Spiel speichern \n 6 - löse Sudoku\n 7 - Beenden\n");

      
        if (scanf("%d", &e) != 1) // Überprüft, ob die Eingabe eine gültige Zahl ist
        {
            printf("Falsche Eingabe\n");
            while (getchar() != '\n'); // Eingabepuffer leeren
            continue; // Zurück zum Menü
        } 

    
        switch (e)
        {
        case 1:
          
            printf("Wählen Sie einen Schwierigkeitsgrad:\n");
            printf(" 1 - Easy\n 2 - Medium\n 3 - Hard\n");

            if (scanf("%d", &e) != 1) // Überprüft, ob die Eingabe eine Zahl ist
            {
                printf("Falsche Eingabe\n");
                while (getchar() != '\n'); // Eingabepuffer leeren
                continue; // Zurück zum Menü
            }

           
            switch (e)
            {
                case 1:
                    open_file(&fp, easy); // Datei öffnen
                    load_file(fp, board); // Daten in das Board laden
                    close_file(fp, easy); // Datei schließen
                    break;

                case 2:
                    open_file(&fp, medium);
                    load_file(fp, board);
                    close_file(fp, medium);
                    break;

                case 3:
                    open_file(&fp, hard);
                    load_file(fp, board);
                    close_file(fp, hard);
                    break;

                break;
            }
            break;

        case 2:
            // Aktuelles Sudoku-Board anzeigen
            printBoard(board);
            break;

        case 3: 
            // Spielmodus: Benutzer bearbeitet das Board
            while(1)
            {
                printBoard(board); // Aktuelles Board anzeigen
                set_board_element(board); // Benutzer ändert eine Zelle
                printBoard(board); // Aktualisiertes Board anzeigen

                // Abfrage, ob das Spiel fortgesetzt werden soll
                printf("Moechten Sie das Spiel fortsetzen? (1 fuer Ja, 0 fuer Nein): ");
                scanf("%d", &continuePlaying);
                system("cls"); // Konsole leeren
                if (continuePlaying != 1) 
                {
                    while (getchar() != '\n'); // Eingabepuffer leeren
                    break; // Schleife verlassen
                }
            }
            break; 
        
        case 4:
            // Rückgängig machen: vorherigen Spielstand wiederherstellen
            undo(board);
            printBoard(board);
            break;

       case 5: 
            // Spielstand speichern
            printf("Bitte geben Sie einen Dateinamen ein: ");
            scanf("%99s", dateiname); // Dateiname einlesen
            speichern(board, dateiname); // Spielstand speichern
            break;
            
        case 6:
            // Sudoku automatisch lösen
            solve(board, 0, 0); 
            system("cls"); // Konsole leeren
            printBoard(board); 
            break; 

        case 7:
            // Programm beenden
            running = 0;
            break;

        default:
            // Falsche Eingabe, Hinweis ausgeben
            printf("Falsche Eingabe, versuchen Sie es erneut!\n");
            break;
        }
    }
}