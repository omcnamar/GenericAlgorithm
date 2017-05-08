#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>

using namespace std;

//Generic Algorithm 
//1) "Randomly" generate candidates 
//2) Apply fitness function "Evaluate"
//2.5) sort
//3) crossover
//4) mutate
//5) repeat

int candidates = 6;
int candidateSize = 5;
float keep = 0.5;
float mutateRate = 0.2;


struct sample{
    string code;
    int value;
    int eval;
};

void showSamples(vector<sample> samplesIn);
int toInt(string sampleIn);
int evaluate(int valueIn);
void crossover(vector<sample>& samplesIn);
void mutate(vector<sample>& samplesIn);

int main()
{
    srand(time(NULL));
	cout << "Generic Algorithm" << endl;
    //variables
    vector<sample> samples;
    
    //generate sample population
    cout << "Generate sample population" << endl;
    for(int i = 0; i < candidates; i++){
        
        sample tempSample;
        tempSample.code ="";
        tempSample.value = 0;
        tempSample.eval = -1;
        
        for(int j = 0; j < candidateSize; j++){
            int chance = rand() % 100;
            if ( chance >= 50){
                tempSample.code += "1";
            }else{
                tempSample.code += "0";
            }
        }
        
        samples.push_back(tempSample);
    }
    
    int loops = 10;
    while(loops > 0){
        cout<< "Convert to decimal "<<endl;
        for(unsigned int i = 0; i < samples.size(); i++){
            samples[i].value = toInt(samples[i].code);
        }
        
        cout <<endl<< "Evaluate to decimal "<<endl;
        for(unsigned int i = 0; i < samples.size(); i++){
            samples[i].eval = evaluate(samples[i].value);
        }
        
        showSamples(samples);
        //sort
        for(int i = 0; i < samples.size()-1; i++){
            for(int j = i; j < samples.size(); j++){
                if(samples[i].eval < samples[j].eval){
                    sample temp = samples[i];
                    samples[i] = samples[j];
                    samples[j] = temp;
                }
            }
        }
        cout<<"Sorted..."<<endl;
        //print
        showSamples(samples);
        
        crossover(samples);
        //convert to decimal again 
        for(unsigned int i = 0; i < samples.size(); i++){
            samples[i].value = toInt(samples[i].code);
        }
        //evaluate again
        for(unsigned int i = 0; i < samples.size(); i++){
            samples[i].eval = evaluate(samples[i].value);
        }
        
        cout<<"After crossover." << endl;
        showSamples(samples);
        
        //mutate
        mutate(samples);
        //convert to decimal again 
        for(unsigned int i = 0; i < samples.size(); i++){
            samples[i].value = toInt(samples[i].code);
        }
        //evaluate again 
        for(unsigned int i = 0; i < samples.size(); i++){
            samples[i].eval = evaluate(samples[i].value);
        }
        cout<<"After mutate..." << endl;
        showSamples(samples);
        loops--;
    }
    
    return 0;
}

void mutate(vector<sample>& samplesIn){
    for(int i = 0; i < samplesIn.size(); i++){
        //should we mutate?
        if(((rand()%10) / (float)(10)) < mutateRate){
            //which element to mutate?
            int mutateIndex  = rand() % candidateSize;
            
            if(samplesIn[i].code[mutateIndex] == '0'){
                samplesIn[i].code[mutateIndex] = '1';
            }else{
                samplesIn[i].code[mutateIndex] = '0';
            }
        }
    }
}

void crossover(vector<sample>& samplesIn){
    vector<sample> results;
    for(int i = 0; i < (candidates * keep); i++){
        //choose samples from the top 'keep' candidates
        sample one = samplesIn[(rand() % candidates)*keep];
        sample two = samplesIn[(rand() % candidates)*keep];
        
        sample result1;
        sample result2;
        
        //choose a cut point
        int cut = rand() % candidateSize;
        
        //build new candidates
        result1.code = "";
        result2.code = "";
        
        result1.value = 0;
        result2.value = 0;
        
        result1.eval = 0;
        result2.eval = 0;
        
        for(int j = 0; j < candidateSize; j++){
            if(j < cut){
                result1.code += one.code[j];
                result2.code += two.code[j];
            }else{
                result2.code += one.code[j];
                result1.code += two.code[j];
            }
        }
        
        results.push_back(result1);
        results.push_back(result2);
    }
    
    //store results in original vector 
    for(int i  = 0; i < results.size(); i++){
        samplesIn[i] = results[i];
    }
    
    return;
}

void showSamples(vector<sample> samplesIn){
    for(unsigned int i = 0; i < samplesIn.size(); i++){
        cout << "Sample " << i << " : "<< samplesIn[i].code <<" |\t";
        cout << "value " << i << " : "<< samplesIn[i].value << " |\t ";
        cout << "eval " << i << " : "<< samplesIn[i].eval << endl;
    }
}

int toInt(string sampleIn){
//    int in = Integer.parseInt(samplesIn);
//    return in;
    int value = 0;
    int power = 0;
    
    for(int i = sampleIn.size() - 1; i >=0 ; i--){
        value+=(pow(2, power++)*(sampleIn[i] - '0'));
    }
    return value;
}

int evaluate(int valueIn){
    return pow(valueIn, 2);
}