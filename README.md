WC-Kommando in C (mit Threads)
Überblick
Dieses Projekt implementiert eine erweiterte Version des Linux-Befehls wc (Word Count) in C. Das Programm zählt die Anzahl der Zeilen und Wörter in einer Datei und gibt das Ergebnis auf der Standardausgabe (stdout) aus. Die Byte-Zählung aus wc wurde nicht implementiert.
Falls mehrere Dateien angegeben werden, nutzt das Programm Threads, um die Verarbeitung zu parallelisieren und die Laufzeit zu optimieren.
Funktionen
Das Programm unterstützt folgende Funktionen:
	•	Zählt Zeilen (\n-Zeichen)
	•	Zählt Wörter (durch Leerzeichen getrennt)
	•	Bestimmt die längste Zeile
	•	Verarbeitet mehrere Dateien parallel mit Threads
	•	Unterstützt Dateieingabe (stdin) zur Verarbeitung von Pipelinedaten
	•	Unterstützt verschiedene Flags, um die Ausgabe zu steuern
Kompilierung
Das Programm wird mit gcc kompiliert. Nutze das bereitgestellte Makefile und führe folgenden Befehl im Terminal aus:
sh

make all
Alternativ kann das Programm manuell kompiliert werden mit:
sh

gcc -Wall -std=c99 -pthread -g -c src/main.c -o src/main.o
gcc -Wall -std=c99 -pthread -g -c src/wc_functions.c -o src/wc_functions.o

# Ausführbare Datei compilieren.
gcc -Wall -std=c99 -pthread -g -o new_wc src/main.o src/wc_functions.o

Ausführung
Das Programm kann mit einer oder mehreren Dateien oder über stdin verwendet werden.
	•	Es ist möglich, einzelne oder mehrere Dateien parallel zu verarbeiten.
	•	Durch das Hinzufügen von Flags kann die Ausgabe gefiltert oder lesbarer dargestellt werden.
	•	Zudem kann das Programm in Pipelines genutzt werden.
	•	Wichtig: Flags und Dateinamen müssen mit einem Leerzeichen getrennt sein.
Beispiele:
sh

./new_wc test.txt
./new_wc file1.txt file2.txt
cat test.txt | ./new_wc
./new_wc -l file1.txt file2.txt
Threads & Synchronisation
	•	Falls mehrere Dateien angegeben werden, wird für jede Datei ein eigener Thread erstellt.
	•	Jeder Thread verarbeitet und speichert die Daten unabhängig.
	•	Schließlich sammelt der Hauptthread die Ergebnisse und gibt sie aus.
Fehlermeldungen bei ungültigen Dateinamen und leeren Dateien
Falls eine Datei nicht existiert oder ein falscher Dateiname angegeben wird, gibt das Programm eine Fehlermeldung aus.
sh

./new_wc nicht_existierend.txt
# Ausgabe: Datei [Dateinname] nicht gefunden!
sh

./new_wc leere_Datei.txt
# Ausgabe: Datei [Dateiname] ist leer!
