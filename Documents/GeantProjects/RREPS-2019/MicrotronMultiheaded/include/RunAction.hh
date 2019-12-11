#ifndef B2RunAction_h
#define B2RunAction_h 1

//Создано специально для проекта http://dev.asifmoda.com/geant4
//Сообщество в facebook  https://www.facebook.com/groups/248240199204054/

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4Accumulable.hh"
#include "ExG4DetectorConstruction01.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Run;
class ActionInitilization;
//class ExG4DetectorConstruction01;

/// Run action class, класс RunAction, выполняется в отдельном потоке,
/// по сути это как один RunManager в однопоточном режиме.
/// Количество частиц которое выполняется в одном  RunAction
/// вычисляется динамически в процессе расчета, оно не фиксированно

class RunAction : public G4UserRunAction
{
public:
    RunAction();
    ~RunAction();
    ///В этой функции выводится прогресс моделирования
    void DisplayProgress(G4int);
    ///Здесь делаем необходимые приготовления перед
    ///запуском счета
    void BeginOfRunAction(const G4Run*);
    ///После расчета как правило с вспомогательных потоков передаем
    ///полученные данные на главный поток, где их объединяем
    ///и выводим в файл
    void EndOfRunAction(const G4Run*);
    ///Объявляем функцию, которую будем использовать для сбора
    ///данных моделирования
    void FillEnergy(G4double);
    //ExG4DetectorConstruction01 angle;

        //rt.GetTargetAngle();
private:
    ///Класс G4Accumulable используется для передачи и объединения
    ///данных моделирования в главном потоке. По умолчанию работает
    ///только с простыми типами, double, int и т.д. однако функциональность
    ///можно расширить за счет пользовательского класса.
    G4Accumulable<G4double> Energy;
    ///Сюда будем записывать колическово смоделированных частиц
    G4int eventsNumber;
    ///Переменная необходимая для вывода прогресса моделирования
    G4int printModulo;
    ///Переменная для записи энергии частиц
    G4double particlesEnergy;

};

#endif
