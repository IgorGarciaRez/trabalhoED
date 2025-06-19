#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;

const int BLOCK_SIZE = 1000;
const int NUM_TEMP_FILES = 20;

struct Athlete{
    int id;
    char name[100];
    char city[60];
    char sport[60];
    char event[120];
    char noc[3];
};

//string pra inteiro
int toInt(const string& str){
    //stoi -> string to integer (biblioteca std)
    int num;
    try {
        num = stoi(str);
    } catch (const invalid_argument& e) {
        cerr << "Error: Invalid argument for stoi - " << e.what() << endl;
    } catch (const out_of_range& e) {
        cerr << "Error: Number out of range for stoi - " << e.what() << endl;
    }
    return num;
}

//conversor de csv para binario
void csvToBin(const string& csvName, const string& binName) {
    ifstream input(csvName.c_str());
    if (!input.is_open()) throw runtime_error("Erro ao abrir arquivo de entrada: " + csvName);
    
    ofstream binary(binName.c_str(), ios::binary);
    if (!binary.is_open()) throw runtime_error("Erro ao abrir arquivo binario: " + binName);
    
    string line;
    
    // Pula a primeira linha (cabeçalho)
    getline(input, line);

    while (getline(input, line)) {
        if (line.empty()) continue; // Pula linhas vazias
        
        istringstream ss(line);
        Athlete a;
        string field;

        // inicializar estrutura
        a.id = 0;
        a.name[0] = '\0';
        a.city[0] = '\0';
        a.sport[0] = '\0';
        a.event[0] = '\0';
        a.noc[0] = '\0';

        if (getline(ss, field, ',')) {
            a.id = toInt(field);
        }
        if (getline(ss, field, ',')) {
            strncpy(a.name, field.c_str(), sizeof(a.name) - 1);
            a.name[sizeof(a.name) - 1] = '\0';
        }
        if (getline(ss, field, ',')) {
            strncpy(a.city, field.c_str(), sizeof(a.city) - 1);
            a.city[sizeof(a.city) - 1] = '\0';
        }
        if (getline(ss, field, ',')) {
            strncpy(a.sport, field.c_str(), sizeof(a.sport) - 1);
            a.sport[sizeof(a.sport) - 1] = '\0';
        }
        if (getline(ss, field, ',')) {
            strncpy(a.event, field.c_str(), sizeof(a.event) - 1);
            a.event[sizeof(a.event) - 1] = '\0';
        }
        if (getline(ss, field)) { // ultimo campo não tem vírgula
            strncpy(a.noc, field.c_str(), sizeof(a.noc) - 1);
            a.noc[sizeof(a.noc) - 1] = '\0';
        }
        binary.write(reinterpret_cast<char*>(&a), sizeof(Athlete));
    }    
    input.close();
    binary.close();
}

//ordenação dos elementos dentro do bloco - descrescente
void orderBlock(Athlete block[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (block[j].id < block[j + 1].id) {
                Athlete temp = block[j];
                block[j] = block[j + 1];
                block[j + 1] = temp;
            }
        }
    }
}

//ler os elementos do bloco
int readBlock(ifstream& file, Athlete block[]){
    int read = 0;
    bool limit = false;
    while(read < BLOCK_SIZE && limit == false) {
        file.read(reinterpret_cast<char *>(&block[read]), sizeof(Athlete));
        if(file.gcount() < sizeof(Athlete)){
            limit = true;
        }else{
            read++;
        }
    }
    return read;
}

//adiciona blocos nos arquivos
void writeBlock(int indexFile, Athlete newBlock[], int newSize){
    ostringstream oss;
    oss << "temp" << indexFile << ".bin";
    string nameTemp = oss.str();

    ifstream file(nameTemp.c_str(), ios::binary);
    Athlete* block = NULL;
    int size = 0;

    if(file.is_open()){
        file.seekg(0, ios::end);
        long byteSize = file.tellg();
        size = byteSize / sizeof(Athlete);
        if(size > 0){
            block = new Athlete[size];
            file.seekg(0, ios::beg);
            file.read(reinterpret_cast<char*>(block), byteSize);
        }
        file.close();
    }

//cria array combinado (novo bloco + existente) -> copia bloco novo -> copia bloco existente
    int sizet = newSize + size;
    Athlete* combinedBlock = new Athlete[sizet];
    for (int i = 0; i < newSize; ++i) {
        combinedBlock[i] = newBlock[i];
    }
    for (int i = 0; i < size; ++i) {
        combinedBlock[newSize + i] = block[i];
    }
    orderBlock(combinedBlock, sizet);
    
    ofstream output(nameTemp.c_str(), ios::binary);
    for (int i = 0; i < sizet; ++i) {
        output.write(reinterpret_cast<char*>(&combinedBlock[i]), sizeof(Athlete));
    }
    output.close();
    if (block) delete[] block;
    delete[] combinedBlock;
}

void createTempReuseFiles(const string& binName){
    ifstream input(binName.c_str(), ios::binary);
    if(!input.is_open()) throw runtime_error("Erro ao abrir arquivo binario: " + binName);
    Athlete* block = new Athlete[BLOCK_SIZE];
    int currentIndex = 0;
    int totalBlocks = 0;
    int totalRegisters = 0;
    
    bool hasData = true;
    while(hasData){
        int read = readBlock(input, block);
        if(read != 0){
            orderBlock(block, read);
            writeBlock(currentIndex, block, read);
            totalRegisters+=read;
            totalBlocks++;
            currentIndex = (currentIndex+1) % NUM_TEMP_FILES;
        }else{
            hasData = false;
        }
    }
    input.close();
    delete[] block;
}

//intercalacao de arquivos temporarios
void mergeTempFiles(const string& outputName){
    ifstream* inputs = new ifstream[NUM_TEMP_FILES];
    Athlete* athletes = new Athlete[NUM_TEMP_FILES];
    bool* actives = new bool[NUM_TEMP_FILES];
    
    for(int i = 0; i < NUM_TEMP_FILES; i++){
        ostringstream oss;
        oss << "temp" << i << ".bin";
        inputs[i].open(oss.str().c_str(), ios::binary);
        if(inputs[i].read(reinterpret_cast<char*>(&athletes[i]), sizeof(Athlete))){
            actives[i] = true;
        }else{
            actives[i] = false;
        }
    }

    ofstream output(outputName.c_str(), ios::binary);
    if(!output.is_open()) throw runtime_error("Erro ao abrir arquivo: " + outputName);
    int registersWritten = 0;
    bool hasFinished = false;
    while(!hasFinished){
        int maxId = -1;
        int index = -1;
        for (int j = 0; j < NUM_TEMP_FILES; ++j) {
            if (actives[j] && (index == -1 || athletes[j].id > maxId)) {
                maxId = athletes[j].id;
                index = j;
            }
        }
        if(index != -1){
            output.write(reinterpret_cast<char*>(&athletes[index]), sizeof(Athlete));
            registersWritten++;
            if (inputs[index].read(reinterpret_cast<char*>(&athletes[index]), sizeof(Athlete))) {
                actives[index] = true;
            } else {
                actives[index] = false;
            }
        }else{
            hasFinished = true;
        }
    }
    for (int i = 0; i < NUM_TEMP_FILES; ++i) {
        inputs[i].close();
    }
    output.close();

    delete[] inputs;
    delete[] athletes;
    delete[] actives;
}

void binaryToCsv(const string& binName, const string& csvName){
    ifstream input(binName.c_str(), ios::binary);
    if(!input.is_open()) throw runtime_error("Erro ao abrir arquivo binario: " + binName);
    ofstream output(csvName.c_str());
    if(!output.is_open()) throw runtime_error("Erro ao abrir arquivo: " + csvName);

    Athlete a;
    while(input.read(reinterpret_cast<char*>(&a), sizeof(Athlete))){
        output << a.id << ","
              << a.name << ","
              << a.city << ","
              << a.sport << ","
              << a.event << endl;
    }
    input.close();
    output.close();
}

void cleanTempFiles(){
    cout << "Limpando arquivos temporários" << endl;
        for (int i = 0; i < NUM_TEMP_FILES; ++i) {
            ostringstream oss;
            oss << "temp" << i << ".bin";
            remove(oss.str().c_str());
        }
}

int main(){
    string csvName = "data_athlete_event.csv";
    string binName = "dados.bin";

    csvToBin(csvName, binName);
    ifstream file(binName.c_str(), ios::binary | ios::ate);
    if (file.is_open()) {
        long tamanho = file.tellg();
        cout << "Tamanho do arquivo binário: " << tamanho << " bytes" << endl;
        cout << "Número de registros: " << tamanho / sizeof(Athlete) << endl;
        file.close();
    }else{
        throw runtime_error("Erro ao abrir arquivo: " + binName);
    }

    createTempReuseFiles(binName);
    string finalOutput = "saida_ordenada.bin";
    mergeTempFiles(finalOutput);
    string finalCsv = "saida_ordenada.csv";
    binaryToCsv(finalOutput, finalCsv);
    cleanTempFiles();
    
    return 0;
}