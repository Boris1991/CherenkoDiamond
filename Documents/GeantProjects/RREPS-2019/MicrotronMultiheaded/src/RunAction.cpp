//Создано специально для проекта http://dev.asifmoda.com/geant4
//Сообщество в facebook  https://www.facebook.com/groups/248240199204054/

#include "RunAction.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "Randomize.hh"
#include "G4AccumulableManager.hh"
#include "ExG4DetectorConstruction01.hh"
#include "B4Analysis.hh"
#include "B4Analysis.hh"

using namespace CLHEP;
using namespace std;

//Конструктор класса RunAction, обратите внимание, что переменные G4Accumulable
//как Energy(0) должны быть объявлены с неким начальным значением
RunAction::RunAction()
    : G4UserRunAction(),Energy(0)
{
    // Register accumulable to the accumulable manager
    //Создаем экземпляр класса управления (менеджера) переменных G4Accumulable
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    //В нем регистрируем все переменные G4Accumulable для того что бы
    //они коректно обрабатывались
    accumulableManager->RegisterAccumulable(Energy);
    
	
	auto analysisManager = G4AnalysisManager::Instance();
	  analysisManager->SetVerboseLevel(4);
  analysisManager->SetNtupleMerging(true);
	analysisManager->CreateH1("electronSpectra","electron spectra", 50, 1.4*eV, 6*eV);
	analysisManager->CreateH2("XY","", 101, -40, 40, 101, -40, 40);
}

//Деструктор
RunAction::~RunAction()
{
	 delete G4AnalysisManager::Instance();  
	}

//Функция выполняется перед началом запуска потока моделирования
void RunAction::BeginOfRunAction(const G4Run* aRun)
{   
	  auto analysisManager = G4AnalysisManager::Instance();
	G4String fileName = "B4";
  analysisManager->OpenFile(fileName);
    //Берем полное число частаиц, которое будет запущено
    eventsNumber = aRun->GetNumberOfEventToBeProcessed();
    printModulo = eventsNumber/100;
    if (printModulo == 0)
        printModulo = 1;
    //Обнуляем переменную, в нее будем записывать энергию
    //частиц приходящих в детектор
    particlesEnergy = 0;

    // inform the runManager to save random number seed
    //Сообщаем G4RunManager -у сохранить зерно для генератора случайных чисел
    G4RunManager::GetRunManager()->SetRandomNumberStore(false);

    // reset accumulables to their initial values
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    //Сбрасываем значения накапливаемых переменных accumulables на их начальные значения
    accumulableManager->Reset();
    
 
}

//Функция, в которой суммируем энергиию частиц попавших в детектор
void RunAction::FillEnergy(G4double energy)
{	
    particlesEnergy += energy ;
}
//Функция отображения статуса моделирования
void RunAction::DisplayProgress(G4int eventID)
{
    if (eventID%printModulo == 0)
        G4cout << "Progress: " << 100*eventID/eventsNumber << "%\r" << std::flush;
}
//Функция выполняемая в конце выполнения потока
//Следуюет помнить, что есть работающие потоки, которые считаю
//И есть главный процесс Master, в котором моделирование не происходит
//но он завершается последним и в нем собираются все данные G4AccumulableManager-ом
void RunAction::EndOfRunAction(const G4Run* )
{
    //Проверяем, если не главный процесс, то копируем значение энергии
    //частиц в G4Accumulable
    if (!IsMaster()) {
        Energy=particlesEnergy;
        
       
    };
    // Merge accumulables
    // Передаем данные в главный поток
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Merge();
    if (IsMaster()) {//Выполняем в главном потоке
        G4cout
                << G4endl
                << "--------------------End of Global Run-----------------------";
        G4cout
                << G4endl;
        //Из G4Accumulable берем значение
        particlesEnergy=Energy.GetValue();
        
     
    }
    else {//Если у нас вычислительный поток, не главный
        G4cout
                << G4endl
                << "--------------------End of Local Run------------------------";
    }
     auto analysisManager = G4AnalysisManager::Instance();
     analysisManager->Write();
     analysisManager->CloseFile();
}
