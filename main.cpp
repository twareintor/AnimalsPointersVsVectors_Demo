//Microsoft (R) C/C++ Optimizing Compiler Version 19.00.23506 for x64

#include <iostream>

#define USE_POINTERS
#undef USE_POINTERS

#ifdef USE_POINTERS
#else
#include <vector>
int g_id = 0;
#endif

class CAnimal
{
#ifdef USE_POINTERS
    //
#else
    int m_id;
public:
    CAnimal():m_id(++g_id){}
    int getId(){return m_id;}
#endif
};

class CHerd
{
#ifdef USE_POINTERS
    // pointer version
    CAnimal* m_animals[0x100];
    int m_animalCount;
    
public:
    CHerd() = delete;
    CHerd(CAnimal** animals, int nHowMany = 1)
    {
        for(int i = 0; i<nHowMany; i++)
        {
            m_animals[i] = animals[i];
        }
        m_animalCount = nHowMany;     
    }
    CAnimal** getAnimals(){return m_animals;}
    int getAnimalCount(){return m_animalCount;}
    void addAnimals(CAnimal** animals, int nHowMany = 1)
    {
        bool bFoundHere = false;
        int p = 0;
        for(int i = 0; i<nHowMany; i++)
        {
            for(int j = 0; j<m_animalCount; j++)
            {
                if(animals[i] == m_animals[j])
                {
                    std::cout<<"animal "<<(void*)animals[i]<<" already here\n";
                    bFoundHere = true;
                    nHowMany--;
                    p++;
                }
            }
            if(!bFoundHere)
            {
                m_animals[m_animalCount+i-p] = animals[i];
            }
            bFoundHere = false;
        }
        m_animalCount+=nHowMany;
    }
    void removeAnimals(CAnimal** animals, int nHowMany = 1)
    {
        bool bFoundHere = false;
        for(int i = 0; i<nHowMany; i++)
        {
            int f = 0;
            for(int j = 0; j<m_animalCount; j++)
            {
                if(animals[i] == m_animals[j])
                {
                    bFoundHere = true;
                    f = j;
                    break;
                }
            }
            if(bFoundHere)
            {
                for(int j = f; j<m_animalCount-1; j++)
                {
                    m_animals[j] = m_animals[j+1];
                }
                m_animalCount--;
            }
            else
            {
                std::cout<<"animal "<<(void*)animals[i]<<" not found here\n";
            }
        }
    }
#else
    // vector version
    std::vector<CAnimal> m_animals;
public:
    CHerd() = delete;
    CHerd(std::vector<CAnimal>& animals):m_animals(animals){}
    std::vector<CAnimal>& getAnimals(){return m_animals;}
    int getAnimalCount(){return m_animals.size();}
    void addAnimals(std::vector<CAnimal>&& animals)
    {
        bool bFoundHere = false;
        for(auto&& it: animals)
        {
            for(auto&& itm: m_animals)
            {
                if(it.getId() == itm.getId())
                {
                    std::cout<<"animal "<<it.getId()<<" already here\n";
                    bFoundHere = true;
                }
            }
            if(!bFoundHere)
            {
                m_animals.push_back(it);
            }
            bFoundHere = false;
        }
    }
    void removeAnimals(std::vector<CAnimal>&& animals)
    {
        bool bFoundHere = false;
        for(auto&& it: animals)
        {
            int f = 0;
            for(auto&& itm: m_animals)
            {
                if(it.getId() == itm.getId())
                {
                    bFoundHere = true;
                    break;
                }
                f++;
            }
            if(bFoundHere)
            {
                m_animals.erase(m_animals.begin() + f);
            }
            else
            {
                std::cout<<"animal "<<it.getId()<<" not found here\n";
            }
        }
        
    }
#endif
};


template <class T>
int test_animal_in_herd()
{
#ifdef USE_POINTERS 
#else
#endif
    return 0;
}


int main()
{
    std::cout<<"Game Over!\n";
    return 0;
}

