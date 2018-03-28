#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <vector>
#include <string>
#include <string.h>

#include "priority_queue.hpp"

using namespace std;

typedef priority_queue<float,std::less<float>> PQUEUE;
typedef std::vector<std::string> FILES;

FILES get_block_files(const char* path);
void analyse(PQUEUE& queue, float* buffer, int buflen);

int main(int argc, char** argv)
{
    const char* datapath = "floats";

    if((access(datapath,F_OK)) == -1)   
    {   
        cerr << "Data directory \"" << datapath << "\" is not exist!" << endl;
        cerr << "Use creator tool to generate 100000000 floats first." << endl;
        return 0;
    }

    //参阅建立一个队列使用小根堆的方式
    //小根堆的方式分析上发性能更优秀，只要比队列首元素小的数据无需入队，比较相当高效！分析过程可以看analyse函数
    PQUEUE pq(10000);
    
    //获取datapath目录下的所有文件名
    FILES vt_files = get_block_files(datapath);

    //遍历vt_files每一个文件，进行读取数据并解析
    const int MAX_READ_BYTE = 1024*100;
    char* buffer = (char*)malloc(MAX_READ_BYTE);

    FILES::iterator it = vt_files.begin();
    int count = 0;
    int files = vt_files.size();
    int readlen = 0;

    while(it != vt_files.end())
    {
        ifstream f_data;
        f_data.open(it->c_str(),ios_base::binary);
        if(f_data.is_open())
        {
            cout << "\r";
            cout << "Anaylsing " << setw(2) << (int)((1.0f * ++count/files) * 100.0f) << "\%"
                 << "(" << it->c_str() << ")";
            cout.flush();

            f_data.seekg(0,ios::end);
            long fsize = f_data.tellg();
            f_data.seekg(0,ios::beg);
            readlen = (fsize < MAX_READ_BYTE) ? fsize : MAX_READ_BYTE;
            while (f_data.read(buffer, readlen))
            {
                //分析数据
                analyse(pq,(float*)buffer,readlen);
                fsize -= MAX_READ_BYTE;
                if (fsize <= MAX_READ_BYTE)
                {
                    readlen = fsize;
                }
                if (fsize < 0)
                {
                    break;
                }
            }

            f_data.close();
        }
        
        ++it;
    }

    free(buffer);

    cout << "\r";
    cout << "Anaylse complete!                                                                    ";
    cout << endl;
    cout.flush();


    //所有文件数据分析完成后，下面代码是把结果输出到终端，及result.txt文件。
    //由于小根堆存放结果，而显结果需要从大到小显示比较友好。所以特申请了float* result一块内存
    //result保存从大到小的值。

    cout << "Generating result file... ";
    int q_size = pq.size();
    float* result = (float*)malloc(sizeof(float)*q_size);
    float* _f = result + q_size;
    while(!pq.empty())
    {
        pq.dequeue(*(--_f));
    }

    //写result.txt文件
    std::ofstream outfile("result.txt",std::ios::binary | std::ios::out);
    outfile << setiosflags(ios::fixed);
    outfile << setprecision(3);
    if(outfile.is_open())
    {
        for(int i = 1; i <= q_size; ++i)
        {
            outfile << setw(12) << result[i - 1];
            if(i % 10 == 0)
            {
                outfile << endl;
            }
        }
        outfile << endl;
        outfile.close();
    }

    //标准输出上也显示些东西
    cout.flush();
    cout << "\r";
    cout << "Generate result file success!              " << endl;
    cout << "The " << q_size << " largest float are : " << endl;
    cout << setiosflags(ios::fixed);
    cout << setprecision(3);
    for(int i = 1; i <= q_size; ++i)
    {
        cout << setw(12) << result[i - 1];
        if(i % 8 == 0)
        {
            cout << endl;
        }
        if(i >= 200)
        {
            cout << endl;
            cout << "        ...... If want to see more, you can see the file \"result.txt.\"" << endl;
            break;
        }
    }
    cout << endl; 

    free(result);

    return 0;
}

FILES get_block_files(const char* path)
{
    FILES vt_files;
    //遍历datapath目录下的所有*.f文件
    DIR* dfd;
    struct dirent* _dp;
    if ((dfd = opendir(path)) == NULL)
    {
        cerr << "can't open " << path << endl;
        cerr << strerror(errno) << endl;
        return vt_files;
    }
    else
    {
        while ((_dp = readdir(dfd)) != NULL)
        {
            if (strncmp(_dp->d_name, ".", 1) == 0)
            {
                //跳过当前目录和上一层目录以及隐藏文件
                continue; 
            }

            std::string item = path;
            item += "/";
            item += _dp->d_name;

            struct stat fs;
            if (stat(item.c_str(), &fs) == -1)
            {
                cerr << "cannot access the file : " << item;
                continue; 
            }

            if ((fs.st_mode & S_IFMT) != S_IFDIR)
            {
                vt_files.push_back(item);
            }
        }
    }
    closedir(dfd);

    return vt_files;
}

void analyse(PQUEUE& q, float* buffer, int buflen)
{
    if(buflen % sizeof(float) != 0)
    {
        return;
    }

    int nums = buflen / sizeof(float);

    for(int i = 0; i < nums; ++i)
    {
        // if(i > 0 && i % 10 == 0)
        // {
        //     cout << endl;
        // }
        // cout << setw(8) << buffer[i];
        // if(i >= 500)
        // {
        //     cout << endl << "......" << endl;
        //     break;
        // }
        float e = *(buffer + i);
        if(!q.enqueue(e))
        {
            float f = 0.0f;
            q.front(f);
            if(e > f)
            {
                float d = 0.0f;
                q.dequeue(d);
                q.enqueue(e);
            }
        }
    }

}
