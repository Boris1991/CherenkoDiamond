//Создано специально для проекта http://dev.asifmoda.com/geant4
//Сообщество в facebook  https://www.facebook.com/groups/248240199204054/

// Подключаем заголовочные файлы
// RunManager - класс из ядра Geant4,
//должен быть включен обязательно для
//моделирования без распаралеливания
//а класс G4MTRunManager используется
//для запуска примера с распаралелливанием
//и только с ним можно моделировать на нескольких
//ядрах одновреммено
#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"//Многопоточный
#else
#include "G4RunManager.hh"//Непараллельный, однопоточное моделирование
#endif
#include "G4UImanager.hh" // Менеджер взаимодействия с пользователем
#include "ExG4DetectorConstruction01.hh" // Структура детектора,
//должен определяться пользователем
//#include "FTFP_BERT.hh" // Подключается физика и частицы
#include "PhysicsList.hh" // Подключается физика и частицы
// используемые в проекте, использов предопределенный в Geant4
#include "ExG4ActionInitialization01.hh" // Пользовательские классы
//для получения данных о процессе моделирования
#ifdef G4UI_USE //Если используется интерфейс пользователя
#include "G4VisExecutive.hh"//Визуализация
#include "G4UIExecutive.hh"//Выбор соответствуещего интерфейса пользователя
#endif

int main(int argc,char** argv)
{
    //Обеспечение песперебойной работы генератора случайных чисел
    CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
    CLHEP::HepRandom::setTheSeed(time(NULL));//Устанавливаем зерно для генератора
    //случайных чисел
// construct the default run manager
// Создание класс G4RunManager, он управляет течением программы и
// управляет событиями при запуске проекта
//Здесь использован ifdef, если при компилировании Geant4 стоял
//указывался флаг G4MULTITHREADED, то будет собран пример
//с многопоточным классом управления запуска моделирования G4MTRunManager
//если флаг не был указан, то Geant4 не поддерживает многопоточное
//моделирование и выполняется в одном потоке с G4RunManager
#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
  //Выбор максимального числа потоков в выполняемой системе (на компьютере)
  runManager->SetNumberOfThreads( G4Threading::G4GetNumberOfCores());
#else
  G4RunManager* runManager = new G4RunManager;
#endif
// set mandatory initialization classes
// Установка обязательный инициализирующих классов
// Создание и определение детекторов и материалов
runManager->SetUserInitialization(new ExG4DetectorConstruction01);
// Создание физического листа - частиц и физических процессов
// в которых они участвуют, используется предопределенный в Geant4
runManager->SetUserInitialization(new PhysicsList);
// Определение начальных частиц, и прочие классы используемые
// для получения данных о частицах в процессе моделирования
runManager->SetUserInitialization(new ExG4ActionInitialization01);
// initialize G4 kernel
// Инициализация ядра Geant4
runManager->Initialize();
//Объявление менеджера визуализации (класса который отвечает за отображение)
G4VisManager* visManager = new G4VisExecutive;
//Инициализация менеджера визуализации
visManager->Initialize();
// get the pointer to the UI manager and set verbosities
// Получение указателя на менеджера взаимодействия с пользователем
// нужен, что бы можно было отправлять команды в проект
G4UImanager* UImanager = G4UImanager::GetUIpointer();
if ( argc == 1 ) {//Если в командной строке нет параметров то запускаем
 //интерактивный режим
// interactive mode : define UI session
#ifdef G4UI_USE
G4UIExecutive* ui = new G4UIExecutive(argc, argv);//Создание интерфейса пользователя
UImanager->ApplyCommand("/control/execute vis.mac");//Отрисовка по умолчанию
ui->SessionStart();//Запуск интерфейса пользователя
delete ui;//Удаление интерфейса пользователя
#endif
}
else {
// batch mode
// Пакетный режим
G4String command = "/control/execute ";//Команда выполнить
G4String fileName = argv[1];//Имя файла из командной строки при запуске проекта
UImanager->ApplyCommand(command+fileName);//Выполнение команды
}
// start a run
// Запуск моделирования, запускаем 3 частицы
//runManager->BeamOn(3);
// job termination
// Окончание работы, вызов деструктора (удаление) G4RunManager
delete runManager;
return 0;
}
