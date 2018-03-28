#include <iostream>
#include <sys/stat.h>
#include <random>
#include <fstream>
#include <iomanip>
using namespace std;

int main(int argc, char** argv)
{
    cout << setiosflags(ios::fixed);
    cout << setprecision(2);
    mkdir("floats", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    const unsigned int TOTALS = 1000000000;
    const unsigned int BLOCK  = 10000000;

    std::default_random_engine e;
    std::uniform_int_distribution<> u1(0,900000); //随机整数部分
    std::uniform_int_distribution<> u2(0,99);     //随机小数部分

    unsigned int curr = 0;
    int block_id = 0;
    float* nums = new float[BLOCK];
    cout.flush();
    while(curr < TOTALS)
    {
        char filename[64] = {0};
        sprintf(filename,"floats/%03d.f",block_id);

        cout << "\r";
        cout << "Writting file : " << filename << "\tTotal : "  <<  setw(2) <<(int)((1.0f * curr/TOTALS) * 100.0f) << "\%";
        cout.flush();

        std::ofstream outfile(filename,std::ios::binary | std::ios::out);
        if (outfile.is_open())
        {       
            for (unsigned int i = 0; i < BLOCK; i++) 
            {
                *(nums + i) = u1(e) + u2(e)/100.f;
            }
            outfile.write((char*)nums,BLOCK*sizeof(float));
            outfile.close();
        }
        block_id++;
        curr += BLOCK;
    } 

    free(nums);

    cout << "\r";
    cout << "Out put "<< TOTALS << " floats successfully!                                                                         " << endl;
    //cout.flush();

    return 0;
}
