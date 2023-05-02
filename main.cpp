#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;
void print_bits(uint8_t bits) //функция для вывода 8-ми битного числа
{
    int N(8);
    for(int i = N - 1; i >= 0; i--) {
        if(bits & ((uint8_t)1 << i))
            cout << "1";
        else
            cout << "0";
    }
    cout << endl;
}
void print_vector(vector<uint8_t> vect)
{
    for(long unsigned int i = 0; i < vect.size(); i++) {
        cout << hex << (int)vect[i];
    }
    cout << endl;
}
void print_vector(vector<vector<uint8_t>> vect)
{
    for(long unsigned int i = 0; i < vect.size(); i++) {
        for(long unsigned int j = 0; j < vect.size(); j++)
            cout << hex << setfill('0') << setw(2) << (int)vect[i][j] << " ";
        cout << endl;
    }
}
uint8_t circle_step(uint8_t byte, int p)
{
    for(int i = 0; i < p; i++) {
        if(byte & 0x01) {
            byte >>= 1;
            byte |= 0x80;
        } else {
            byte >>= 1;
        }
    }
    return byte;
}
vector<vector<uint8_t>> create_S2(vector<uint8_t> S)
{
    vector<vector<uint8_t>> S2;
    for(long unsigned int i = 0; i < S.size(); i++) {
        vector<uint8_t> help_vector;
        for(long unsigned int j = 0; j < S.size(); j++) {
            help_vector.push_back(((uint8_t)S[i] << 4) + S[j]);
        }
        S2.push_back(help_vector);
    }
    return S2;
}
vector<vector<uint8_t>> create_S3(vector<vector<uint8_t>> S)
{
    vector<vector<uint8_t>> S2;
    for(long unsigned int i = 0; i < S.size(); i++) {
        vector<uint8_t> help_vector;
        for(long unsigned int j = 0; j < S[i].size(); j++) {
            help_vector.push_back(circle_step(S[i][j], 4));
        }
        S2.push_back(help_vector);
    }
    return S2;
}
int main()
{
    vector<uint8_t> S = { 0x5, 0xD, 0xF, 0xC, 0xA, 0xB, 0x8, 0x7, 0x1, 0x4, 0x3, 0xE, 0x0, 0x6, 0x9, 0x2 };
    vector<uint8_t> input_16 = { 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF };
    vector<uint8_t> input_8 = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF };
    vector<uint8_t> output;
    int p = 4;
    vector<vector<uint8_t>> S2 = create_S2(S);
    vector<vector<uint8_t>> S3 = create_S3(S2);
    // 1)
    cout << "1) ";
    cout << "Input vector: ";
    print_vector(input_16);
    for(long unsigned int i = 0; i < S.size(); i++) {
        output.push_back(S[input_16[i]]);
    }
    cout << "Output vector: ";
    print_vector(output);
    output.clear();
    //     2)!!Генерация таблицы
    cout << "2) ";
    cout << "Input vector: ";
    print_vector(input_16);
    for(long unsigned int i = 0; i < input_8.size(); i++) {
        output.push_back(S2[input_8[i] & 0x0F][circle_step(input_8[i], p) & 0x0F]);
    }
    cout << "Output vector: ";
    print_vector(output);
    output.clear();
    // 3)
	cout << "3) ";
    cout << "Input vector: ";
    print_vector(input_16);

    for(long unsigned int i = 0; i < input_8.size(); i++) {
        output.push_back(input_8[i] & 0x0F);
        output.push_back(circle_step(input_8[i], p) & 0x0F);
    }
    cout << "Output vector: ";
    print_vector(output);
    output.clear();
    // 4)
	cout << "4) ";
    cout << "Input vector: ";
    print_vector(input_16);
    for(long unsigned int i = 0; i < input_8.size(); i++) {
        output.push_back(S[input_8[i] & 0x0F]);
        output.push_back(S[circle_step(input_8[i], p) & 0x0F]);
    }
    cout << "Output vector: ";
    print_vector(output);
    output.clear();
    // 5)
	cout << "5) Считываем из 1.txt, записываем в 2.txt"<<endl;
    ifstream file_1("/home/user/Projects_C/Project_1/Project_1/Lab_3/1.txt", ios::binary | ios::in);
    ofstream file_2("/home/user/Projects_C/Project_1/Project_1/Lab_3/2.txt", ios::binary | ios::out);
    char byte_out;
    while(file_1.get(byte_out)) {
        uint8_t byte_in;
        byte_in = (S[(byte_out & 0x0F)] << p) | S[(circle_step(byte_out, p) & 0x0F)];
        file_2.write((char*)&byte_in, sizeof(char));
    }
    file_1.close();
    file_2.close();
    // 6)
	cout << "6) ";
    cout << "Input vector: ";
    print_vector(input_16);
    for(long unsigned int i = 0; i < input_8.size(); i++) {
        output.push_back(S3[input_8[i] & 0x0F][circle_step(input_8[i], p) & 0x0F]);
    }
    cout << "Output vector: ";
    print_vector(output);
    output.clear();
    // 7)
	cout << "7) Считываем из 3.txt, записываем в 4.txt"<<endl;
    ifstream file_3("/home/user/Projects_C/Project_1/Project_1/Lab_3/3.txt", ios::binary | ios::in);
    ofstream file_4("/home/user/Projects_C/Project_1/Project_1/Lab_3/4.txt", ios::binary | ios::out);
    while(file_3.get(byte_out)) {
        uint8_t byte_in;
        byte_in = S3[byte_out & 0x0F][circle_step(byte_out, p) & 0x0F];
        file_4.write((char*)&byte_in, sizeof(char));
    }
    file_3.close();
    file_4.close();
    return 0;
}