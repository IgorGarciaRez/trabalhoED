#include <iostream>
#include <fstream> 
#include <string>

using namespace std;

const int BLOCK_SIZE = 4;
const int NUM_TEMP_FILES = 6; // tem que ser par
const int HALF = NUM_TEMP_FILES/2;

void sortBlock(int arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - 1 - i; ++j) {
            if (arr[j] < arr[j+1]) { 
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void distributeBlocks(string inputFileName, string tempFiles[]){
    ifstream inputFile(inputFileName);
    if(!inputFile.is_open()){
        throw runtime_error("Erro ao abrir o arquivo: " + inputFileName);
    }
    
    ofstream outputFiles[HALF];
    //criar os arquivos temporarios
    for(int i = 0; i < HALF; i++){
        outputFiles[i].open(tempFiles[i]);
        if(!outputFiles[i].is_open()){
            for(int j = 0; j < i; j++){
                outputFiles[j].close();
            }
            inputFile.close();
            throw runtime_error("Erro ao criar arquivo temporario: " + tempFiles[i]);
        }
    }

    int block[BLOCK_SIZE];
    int fileIndex = 0;
    int numRead;
    int value;
    bool stillReading = true;

    while(stillReading){
        numRead = 0;
        int tempVal;
        
        // Tenta ler o primeiro número para o bloco
        if (inputFile >> tempVal) {
            block[numRead++] = tempVal;
            // Tenta ler os números restantes para preencher o bloco
            while (numRead < BLOCK_SIZE && (inputFile >> tempVal)) {
                block[numRead++] = tempVal;
            }
            // Se lemos algo, processamos
            if(numRead > 0){
                sortBlock(block, numRead);
                for(int i = 0; i < numRead; i++){
                    outputFiles[fileIndex] << block[i] << " ";
                }
                outputFiles[fileIndex] << endl;
                fileIndex = (fileIndex + 1) % HALF;
            }
        } else {
            // Se não conseguimos ler nem o primeiro número, significa fim do arquivo
            stillReading = false;
        }
    }

    inputFile.close();
    for(int i = 0; i < HALF; i++){
        outputFiles[i].close();
    }
    cout<<"Distribuicao inicial concluida"<<endl;
}

void mergePass(string inputFiles[], int numInputFile, string outputFiles[], int numOutputFile, int blockSize){

    cout<<"Realizando passagem com intercalação"<<endl;

    ifstream inputs[numInputFile];
    for(int i = 0; i < numInputFile; i++){
        inputs[i].open(inputFiles[i]);
        if(!inputs[i].is_open()){
            for(int j = 0; j < i; j++) inputs[j].close();
            throw runtime_error("Não foi possivel abrir o arquivo para intercalação: " + inputFiles[i]);
        }
    }

    ofstream outputs[numOutputFile];
    for(int i = 0; i < numOutputFile; i++){
        outputs[i].open(outputFiles[i]);
        if(!outputs[i].is_open()){
            for(int j = 0; j < i; j++) outputs[j].close();
            for(int j = 0; j < numInputFile; j++) inputs[j].close();
            throw runtime_error("Não foi possivel abrir o arquivo para intercalação: " + outputFiles[i]);
        }
    }

    int currentValue[numInputFile];
    bool hasMoreData[numInputFile];
    int valuesReadInCurrentRun[numInputFile];

    //inicialização das variáveis pré-loop
    for(int i = 0; i < numInputFile; i++){
        if(inputs[i] >> currentValue[i]){
            hasMoreData[i] = true;
            valuesReadInCurrentRun[i] = 1;
        }else{
            hasMoreData[i] = false;
            valuesReadInCurrentRun[i] = 0;
        }
    }

    int outputTurn = 0; // alteernar entre arquivos de saida
    bool allFilesFinished = false;
    //loop principal: continua enquanto houver dados em pelomenos um arquivo
    while(!allFilesFinished){
        int maxVal = -1;
        int maxInd = -1;
        bool foundMax = false;

        for(int i = 0; i < numInputFile; i++){
            if(hasMoreData[i] && (valuesReadInCurrentRun[i] <= blockSize)){
                if(maxInd == -1 || currentValue[i] >= maxVal){
                    maxVal = currentValue[i];
                    maxInd = i;
                    foundMax = true;
                }
            }
        }

        if(foundMax){
            outputs[outputTurn] << maxVal << " ";
            if(inputs[maxInd] >> currentValue[maxInd]){
                valuesReadInCurrentRun[maxInd]++;
            }else{
                hasMoreData[maxInd] = false;
            }
        }else{
            bool anyFileHasMore = false;
            for(int i = 0; i < numInputFile; i++){
                valuesReadInCurrentRun[i] = 0;
                if(inputs[i] >> currentValue[i]){
                    hasMoreData[i] = true;
                    valuesReadInCurrentRun[i] = 1;
                    anyFileHasMore = true;
                }else{
                    allFilesFinished = false;
                }
            }
            if(anyFileHasMore){
                allFilesFinished = true;
            }else{
                outputs[outputTurn] << endl;
                outputTurn = (outputTurn + 1) % numOutputFile;
            }
        }  
    }
    for(int i = 0; i < numInputFile; i++) inputs[i].close();
    for(int i = 0; i < numOutputFile; i++) outputs[i].close();
    cout << "Passagem de intercalação concluída." << endl;
}

int main() {
    // Nomes dos arquivos temporários
    std::string tempFiles[NUM_TEMP_FILES] = {
        "temp1.txt", "temp2.txt", "temp3.txt",
        "temp4.txt", "temp5.txt", "temp6.txt"
    };

    distributeBlocks("entrada.txt", tempFiles);
    int currentBlockSize = BLOCK_SIZE;
    bool usingSet1 = true;

    for (int pass = 0; pass < HALF; ++pass) {
        if (usingSet1) { // Intercala de (temp1, temp2, temp3) para (temp4, temp5, temp6)
            std::string inputSet[] = {tempFiles[0], tempFiles[1], tempFiles[2]};
            std::string outputSet[] = {tempFiles[3], tempFiles[4], tempFiles[5]};
            mergePass(inputSet, 3, outputSet, 3, currentBlockSize);
        } else { // Intercala de (temp4, temp5, temp6) para (temp1, temp2, temp3)
            std::string inputSet[] = {tempFiles[3], tempFiles[4], tempFiles[5]};
            std::string outputSet[] = {tempFiles[0], tempFiles[1], tempFiles[2]};
            mergePass(inputSet, 3, outputSet, 3, currentBlockSize);
        }
        usingSet1 = !usingSet1; // alterna o conjunto de arquivos
        currentBlockSize *= HALF; // aumenta o tamanho dos blocos intercalados
    }

    cout << "\nIntercalação externa balanceada concluída (simulada)." << endl;
    cout << "Verifique os arquivos temporários para entender o processo." << endl;

    // Limpeza: Remover arquivos temporários (opcional)
    for (int i = 0; i < NUM_TEMP_FILES; ++i) {
        remove(tempFiles[i].c_str());
    }
    //remove("input.txt"); // Remover o arquivo de entrada de exemplo
    cout << "Arquivos temporários e de entrada removidos." << endl;

    return 0;
}