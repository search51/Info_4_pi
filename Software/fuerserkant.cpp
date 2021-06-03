/*  Das ist die nicht Laufzeitoptimierte Version
    Diese Version ist funktionsfähig und skaliert sich selbst.
    BITTE NICHT WEITER SCHICKEN! :)
    */

#include <mpi.h>
#include <stdio.h>
#include <fstream>
#include <ctime>

const char OUTPUT_FILE_NAME[] = "output1.txt";
const int MASTER_ROOT_RANK = 0;
const float ALPHA = 0.09;
const int CALCULATING_TIME_SECONDS = 1000;
const int SIZE_OF_STICK = 1000;
const int INITIAL_TEMPERATURE_KELVIN = 0;
const int STICK_OFFSET_POSITION = 5;
const int STICK_OFFSET_TEMPERATURE_KELVIN = 20;
const int ROUNDING_PLACE = 10000; //gerundet wird auf die 1/ROUNDING_PLACE'ste Stelle



int main(int argc, char *argv[]) {

  MPI_Init(&argc, &argv);

  //eigenen Rang und größe des Kommunikators abfragen
  int numtasks, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  //Stick erstellen und befüllen
  printf("Rang %d | Stick erstellen\n", rank);
  auto stickTemperature = new  float[CALCULATING_TIME_SECONDS + 1][SIZE_OF_STICK];
  for (int i = 0; i < SIZE_OF_STICK; i++) {
    stickTemperature[0][i] = INITIAL_TEMPERATURE_KELVIN;
  }


  //Stick an Stelle x mit Offset belegen
  printf("Rang %d | Stick offset\n", rank);
  stickTemperature[0][STICK_OFFSET_POSITION] = STICK_OFFSET_TEMPERATURE_KELVIN;


  //Zeitmessung starten
  printf("Rang %d | Zeitmessung\n", rank);
  std::clock_t startTime;
  if (rank == MASTER_ROOT_RANK) {
	  startTime = std::clock();
  }

  //Stick aufteilen
  printf("Rang %d | Stick aufteilen\n", rank);
  if (SIZE_OF_STICK < numtasks) {
    printf("ERR0: Stab-Groesse ist kleiner als Anzahl-Worker.");
    return 0;
  }
  int untergrenze;
  int obergrenze;

  int abschnittsgroesse = SIZE_OF_STICK / numtasks;

  untergrenze = abschnittsgroesse * rank;
  obergrenze = abschnittsgroesse * (rank + 1) - 1;

  if (rank == (numtasks-1)) {
    obergrenze = SIZE_OF_STICK - 1;
  }

  printf("Rank: %d | Sticksize: %d  Untergrenze: %d  Obergrenze: %d  \n", rank, SIZE_OF_STICK, untergrenze, obergrenze);


  //stick berechnen
  printf("Rang %d | Stick berechnen\n", rank);
  for (int time = 0; time < CALCULATING_TIME_SECONDS; time++) {
    printf("Rang %d | Durchgang %d \n", rank,time);

    //derzeigen Zeitstand für alle Teilnehmer teilen
    MPI_Bcast(stickTemperature[time], SIZE_OF_STICK, MPI_FLOAT, MASTER_ROOT_RANK, MPI_COMM_WORLD);

    //temporaeren Stick erstellen und mit nullen füllen
    float tempStickTemperature[SIZE_OF_STICK];
    for (int i = 0; i < SIZE_OF_STICK; i++) {
      tempStickTemperature[i] = 0;
    }


    for (int xStep = untergrenze; xStep <= obergrenze; xStep++) {

      //temporaeren Stick mit Werten füllen
      if (xStep == 0) {
        tempStickTemperature[xStep] = stickTemperature[time][xStep] + ALPHA * (stickTemperature[time][xStep] - 2 * stickTemperature[time][xStep] + stickTemperature[time][xStep + 1]);
      }
      else if (xStep == SIZE_OF_STICK - 1) {
        tempStickTemperature[xStep] = stickTemperature[time][xStep] + ALPHA * (stickTemperature[time][xStep - 1] - 2 * stickTemperature[time][xStep] + stickTemperature[time][xStep]);
      }
      else {
        tempStickTemperature[xStep] = stickTemperature[time][xStep] + ALPHA * (stickTemperature[time][xStep - 1] - 2 * stickTemperature[time][xStep] + stickTemperature[time][xStep + 1]);

      }
    }
    //temporaere Sticks zusammenführen in Haupttabelle von Rank #0
    MPI_Reduce(tempStickTemperature, stickTemperature[time+1], SIZE_OF_STICK, MPI_FLOAT, MPI_SUM, MASTER_ROOT_RANK, MPI_COMM_WORLD);
  }

  //Zeitmessung Beenden und Differenz berechnen
  if (rank == MASTER_ROOT_RANK) {
	  std::clock_t endTime = std::clock();
	  float diffTime = endTime - startTime;
    diffTime = diffTime / CLOCKS_PER_SEC;
	  printf("Zeit ist: %f s\n", diffTime);
  }


printf("Rang %d | Datei ausgeben\n", rank);
  //in Datei ausgeben
  if (true) {
    std::fstream f;
    f.open(OUTPUT_FILE_NAME, std::ios::out);

    for (int time = 0; time < CALCULATING_TIME_SECONDS; time++) {
      for (int xStep = 0; xStep < SIZE_OF_STICK; xStep++) {
        f << stickTemperature[time][xStep] << ";";
      }
      f << std::endl;
    }
    f.close();
  }


  //Array löschen
  delete[] stickTemperature;
  MPI_Finalize();
}

