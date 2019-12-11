//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file ExG4DetectorConstruction01.cpp
/// \brief Implementation of the ExG4DetectorConstruction01 class

//Создано специально для проекта http://dev.asifmoda.com/geant4
//Сообщество в facebook  https://www.facebook.com/groups/248240199204054/

#include "ExG4DetectorConstruction01.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4TransportationManager.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4GenericMessenger.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExG4DetectorConstruction01::ExG4DetectorConstruction01()
: G4VUserDetectorConstruction(),
            fMessenger(nullptr),
            fTargetAngle(90.*deg), fTargetRotation(nullptr), fTargetPhys(nullptr)
{
fTargetRotation = new G4RotationMatrix();
  fTargetRotation->rotateY(fTargetAngle);
 
  DefineCommands();
 }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExG4DetectorConstruction01::~ExG4DetectorConstruction01()
{ 
    delete fTargetRotation;
    delete fMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//Создаем детекторы

G4VPhysicalVolume* ExG4DetectorConstruction01::Construct()
{  
//                         энергии фотонов
//*******************************************************************
//   рассматриваются длины волн 0.3 мкм -- 0.806 мкм
G4double photonEnergy[] =
            { 1.4*eV, 1.6*eV, 1.8*eV, 2.0*eV, 2.2*eV, 2.25*eV,
              2.3*eV, 2.4*eV, 2.5*eV, 2.6*eV, 2.8*eV, 3.0*eV, 3.2*eV, 
              3.4*eV, 3.6*eV, 3.8*eV, 4.0*eV, 4.2*eV, 
              4.4*eV, 4.6*eV, 4.8*eV, 5.0*eV, 5.2*eV, 
              5.4*eV, 5.6*eV, 5.8*eV, 6.0*eV};
            
const G4int nEntries = sizeof(photonEnergy)/sizeof(G4double);
//*******************************************************************

// Air
//*******************************************************************
 // Lead material defined using NIST Manager
  auto nistManager = G4NistManager::Instance();
// Выбор материала для мира из предопределенных в Geant4, берем воздух
  G4Material* world_mat = nistManager->FindOrBuildMaterial("G4_AIR");
//коэффициент преломления для воздуха

  G4double refractiveIndex0[] =
           { 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
             1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 
              1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00};


 G4MaterialPropertiesTable* myMPT2 = new G4MaterialPropertiesTable();
  myMPT2->AddProperty("RINDEX", photonEnergy, refractiveIndex0, nEntries);
myMPT2->DumpTable();
world_mat->SetMaterialPropertiesTable(myMPT2); 
//**********************************************+************************************** 

             //Quartz
//*******************************************************************

  G4double refractiveIndex1[] =
            /* { 2.400, 2.406, 2.407, 2.411, 2.421, 
              2.427, 2.431, 2.441, 2.455, 2.465, 
              2.473, 2.488, 2.506, 2.524, 2.541, 
              2.561, 2.582, 2.606, 2.639, 2.667, 
               2.691, 2.728, 2.771,2.818};*/
            { 2.400, 2.406, 2.407, 2.411, 2.421, 2.423,
             2.4241, 2.427, 2.4295,2.431, 2.441, 2.455, 2.465, 
              2.473, 2.488, 2.506, 2.524, 2.541, 
              2.561, 2.582, 2.606, 2.639, 2.667, 
               2.691, 2.728, 2.771,2.818};
            /* {1.4531, 1.4536, 1.4541, 1.4546, 1.4552,
              1.4557, 1.4563, 1.4569, 1.4576, 1.4583,
              1.4590, 1.4598, 1.4606, 1.4614, 1.4624,
              1.4634, 1.4644, 1.4656, 1.4668, 1.4681,
              1.4695, 1.4711, 1.4727, 1.4745, 1.4764,
              1.4785, 1.4807, 1.4832, 1.4858, 1.4887};*/
           /* {2.432, 2.432, 2.432, 2.432, 2.432,
              2.432, 2.432, 2.432, 2.432, 2.432,
              2.432, 2.432, 2.432, 2.432, 2.432,
              2.432, 2.432, 2.432, 2.432, 2.432,
              2.432, 2.432, 2.432, 2.432 };*/
            
 assert(sizeof(refractiveIndex1) == sizeof(photonEnergy));

 G4double absorption[] =
           
          /* {500*cm, 500*cm, 500*cm, 500*cm, 500*cm,
             500*cm, 500*cm, 500*cm, 500*cm, 500*cm,
             500*cm, 500*cm, 500*cm, 500*cm, 500*cm,
             500*cm, 500*cm, 500*cm, 500*cm, 500*cm, 
             500*cm, 500*cm, 500*cm, 500*cm};*/
          {5*cm, 5*cm, 5*cm, 5*cm, 5*cm, 5*cm,
           5*cm, 5*cm, 5*cm, 5*cm, 5*cm, 5*cm, 5*cm,
             5*cm, 5*cm, 5*cm, 5*cm, 5*cm,
             5*cm, 5*cm, 5*cm, 5*cm, 5*cm, 
             5*cm, 5*cm, 5*cm, 5*cm};
            /*  {5*mm, 5*mm, 5*mm, 5*mm, 5*mm,
             5*mm, 5*mm, 5*mm, 5*mm, 5*mm,
             5*mm, 5*mm, 5*mm, 5*mm, 5*mm,
             5*mm, 5*mm, 5*mm, 5*mm, 5*mm, 
             5*mm, 5*mm, 5*mm, 5*mm};*/


  assert(sizeof(absorption) == sizeof(photonEnergy));
  
  
   G4double scintilFast[] =
            { 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
              1.20, 0.80, 0.80, 1.80, 0.00, 0.00, 0.00, 
              0.00, 0.00, 0.00, 0.00, 0.00,  
              0.00, 0.00, 0.00, 0.00, 0.00, 
              0.00, 0.00, 0.00, 0.00,  
               };
   assert(sizeof(scintilFast) == sizeof(photonEnergy));
              
   G4double scintilSlow[] =
            /*{ 0.01, 1.00, 2.00, 3.00, 4.00, 
			  5.00, 6.00, 7.00, 8.00, 9.00, 
			  8.00, 7.00, 6.00, 4.00, 3.00, 
			  2.00, 1.00, 0.01, 1.00, 2.00, 
			  3.00, 4.00, 5.00, 6.00, 7.00, 
			  8.00, 9.00, 8.00, 7.00, 6.00, 
			  5.50, 5.00, 4.50, 4.00, 3.50, 
			  3.00, 2.50, 2.00, 1.50, 1.00,
			  0.50, 0.25, 0.1};*/
			 {0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
              0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
              0.00, 0.00, 0.00, 0.00, 0.00,  
              0.00, 0.00, 0.00, 0.00, 0.00, 
              0.00, 0.00, 0.00, 0.00 
               };

  assert(sizeof(scintilSlow) == sizeof(photonEnergy));

  //описываем бериллий
///********************************************************************************

G4double z1, aBe;
aBe = 9.01*g/mole;
G4Element* elBe  = new G4Element("beryllium","Be" , z1 = 4., aBe);

G4double densityBe = 1.85*g/cm3;
G4Material* Beryllium =new G4Material("Beryllium", densityBe, 1);
Beryllium->AddElement(elBe, 1);
///********************************************************************************


  // Описываем кварц:
//*****************************
  G4double z, aSi, aO;
  aSi = 28.085*g/mole;
  aO = 15.999*g/mole;
  G4Element* elSi  = new G4Element("Silicium","Si" , z = 14., aSi);
  G4Element* elO  = new G4Element("Oxigen", "O" , z = 8., aO);
//*****************************
// Option to switch on/off checking of volumes overlaps
  // Опция для включения выключения проверки перекрытия объемов
  //
  //G4bool checkOverlaps = true;
  G4MaterialPropertiesTable* myMPT1 = new G4MaterialPropertiesTable();
//*****************************
     
  G4double density = 2.600*g/cm3;
  G4Material* SiO2 = new G4Material("quartz", density, 2);
  SiO2->AddElement(elSi, 1);
  SiO2->AddElement(elO , 2);  
 SiO2->SetMaterialPropertiesTable(myMPT1); 
//*********************************
 //myMPT1->AddConstProperty("SCINTILLATIONYIELD",5./MeV);

    myMPT1->AddProperty("RINDEX",       photonEnergy, refractiveIndex1,nEntries)
        ->SetSpline(true);
    myMPT1->AddProperty("ABSLENGTH",    photonEnergy, absorption,     nEntries)
        ->SetSpline(true);
    myMPT1->AddProperty("FASTCOMPONENT",photonEnergy, scintilFast,     nEntries)
        ->SetSpline(true);
	myMPT1->AddProperty("SLOWCOMPONENT",photonEnergy, scintilSlow,     nEntries)
        ->SetSpline(true);
        
        
    myMPT1->AddConstProperty("SCINTILLATIONYIELD",1000./MeV);
	myMPT1->AddConstProperty("RESOLUTIONSCALE",1*eV);
	myMPT1->AddConstProperty("FASTTIMECONSTANT", 1.*ns);
	myMPT1->AddConstProperty("SLOWTIMECONSTANT",1.*ns);
	myMPT1->AddConstProperty("YIELDRATIO",0.8);
///******************************************************************************** 

// Get nist material manager
  // Для обучения используем предопределенные в Geant4 материалы
  // Так объявляется менеджер, из которого из можно извлечь
  //
  G4NistManager* nist = G4NistManager::Instance();
  
  // Detector parameters
  // Параметры детектора,
  //
  
  // Материал детектора, здесь вольфрам
  //
  G4Material* det_mat = nist->FindOrBuildMaterial("G4_W");
   
  // Option to switch on/off checking of volumes overlaps
  // Опция для включения выключения проверки перекрытия объемов
  //
  G4bool checkOverlaps = true;

  
  
  // Создание объема для мира, определяется просто сама форма объема, берем параллелепипед
  G4Box* solidWorld =    
    new G4Box("World",                       //its name, название объема
       15*cm, 15*cm, 15*cm);     //its size, его размеры

  // Логический объем, здесь подключается материал, из которого сделан объем
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid, объем
                        world_mat,           //its material, материал объема
                        "World");            //its name, название логического объема
                                             //совпадает с названием объема, но
                                             //для Geant4 это разные объекты
                                             //объем и логический объем

  //Физический объем, а теперь наш логический объем помещае в "ральный" мир
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation, нет вращения
                      G4ThreeVector(),       //at (0,0,0), расположение в центре (0,0,0)
                      logicWorld,            //its logical volume, логический объем этого физического
                      "World",               //its name, название физического объема
                      0,                     //its mother  volume, материнский объем, этот самый первый
                      false,                 //no boolean operation, без логических (булевых) операций
                      0,                     //copy number, номер копии
                      checkOverlaps);        //overlaps checking, флаг проверки перекрытия объемов
                     
  //     
 
//*******************************************************8

//Бериллиевый рассеиватель
 /* G4Box* solidDet0 =
    new G4Box("Detector",                    //its name, имя
        5*mm, 5*mm, 0.025*mm); //its size, размеры

  //Логический объем
  G4LogicalVolume* logicDiff =
    new G4LogicalVolume(solidDet0,            //its solid, объем
                        Beryllium,             //its material, указываем материал детектора
                        "Diffuser");         //its name, его имя



  //Физический объем детектора
  new G4PVPlacement(0,                       //no rotation, так же без вращения
                    G4ThreeVector(0*cm,0,-9.9*cm),//G4ThreeVector(det_sizeXY*0,0,0*cm),         //at (0,0,0)
                    logicDiff,                //its logical volume, подключаем логический объем
                    "Detector",              //its name, имя физического объема
                    logicWorld,              //its mother  volume, родительский логический объем!
                    false,                   //no boolean operation, без булевых операций
                    0,                       //copy number, номер копии
                    checkOverlaps);          //overlaps checking, флаг проверки перекрытия объемов

*/
//******************************************************
G4Box* solidDet =
    new G4Box("Detector",                    //its name, имя
        100*mm, 100*mm, 0.015*mm); //its size, размеры*/

  //Логический объем
  G4LogicalVolume* logicDet =
    new G4LogicalVolume(solidDet,            //its solid, объем
                        world_mat,             //its material, указываем материал детектора
                        "Detector");         //its name, его имя
G4RotationMatrix* detRot = new G4RotationMatrix;// Rotates X and Z axes only
     detRot->rotateY(-54*deg);// Rotates 45 degrees

 //Физический объем детектора
  new G4PVPlacement(0,                       //no rotation, так же без вращения
                    G4ThreeVector(0*mm,0,25*mm),         //at (0,0,0)
                    logicDet,                //its logical volume, подключаем логический объем
                    "Detector",              //its name, имя физического объема
                    logicWorld,              //its mother  volume, родительский логический объем!
                    false,                   //no boolean operation, без булевых операций
                    0,                       //copy number, номер копии
                    checkOverlaps);          //overlaps checking, флаг проверки перекрытия объемов
//для листа
//******************************************************************************************8
  /*//Физический объем детектора
  new G4PVPlacement(0,                       //no rotation, так же без вращения
                    G4ThreeVector(0,0,5*cm),         //at (0,0,0)
                    logicDet,                //its logical volume, подключаем логический объем
                    "Detector",              //its name, имя физического объема
                    logicWorld,              //its mother  volume, родительский логический объем!
                    false,                   //no boolean operation, без булевых операций
                    0,                       //copy number, номер копии
                    checkOverlaps);          //overlaps checking, флаг проверки перекрытия объемов*/
//*********************************************************************************************


  //*********************************************************************************************
 //     
  // Target
  // мишень, также используем параллелепипед
  //  
  G4double shape1_rmina =  0.*mm, shape1_rmaxa = 7.5*mm;
  G4double shape1_hz = 0.15*mm;
  G4double shape1_phimin = 0.*deg, shape1_phimax = 360.*deg;
  
G4Tubs* target=    
    new G4Tubs("Target", 
    shape1_rmina, shape1_rmaxa, shape1_hz, shape1_phimin, shape1_phimax);

//Логический объем
  G4LogicalVolume* logicTar =
    new G4LogicalVolume(target,            //its solid, объем
                        SiO2,             //its material, указываем материал детектора
                        "Target");         //its name, его имя
//Матрица поворота
G4RotationMatrix* yRot = new G4RotationMatrix;// Rotates X and Z axes only
     yRot->rotateY(-fTargetAngle);// Rotates 45 degrees
    //G4double angleRot = fTargetAngle;
  //Физический объем детектора
//std::cout<<"rotate of target is "<<yRot<<std::endl;
//std::cout<<"rotate of target2 is "<<fTargetAngle<<std::endl;
 fTargetPhys =
 new G4PVPlacement(yRot,                       //no rotation, так же без вращения
                    G4ThreeVector(0,0,0*cm),         //at (0,0,0)
                    logicTar,                //its logical volume, подключаем логический объем
                    "Target",              //its name, имя физического объема
                    logicWorld,              //its mother  volume, родительский логический объем!
                    false,                   //no boolean operation, без булевых операций
                    0,                       //copy number, номер копии
                    checkOverlaps);

  //
  //always return the physical World
  //Всегда возвращает физический объем
  //
  return physWorld;
}
void ExG4DetectorConstruction01::SetTargetAngle(G4double val)
{
   
  fTargetAngle = val;
  *fTargetRotation = G4RotationMatrix();  // make it unit vector
  fTargetRotation->rotateY(fTargetAngle);
  //G4double angleRot = fTargetAngle;
 
G4RotationMatrix* yRot = new G4RotationMatrix;// Rotates X and Z axes only
     yRot->rotateY(-fTargetAngle);// Rotates 45 degrees

fTargetPhys->SetRotation(yRot);
    //logicTar->SetRotation(45 deg);
  
  // tell G4RunManager that we change the geometry
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
//std::cout<<"rotate of target2 is "<<GetTargetAngle()<<std::endl;
//std::ofstream file_energy_dep("total_particles_energy.txt", std::ios::app);
        //Выводим в файл
  //      file_energy_dep<<round(fTargetAngle/deg);//<<std::endl;
        //Закрываем поток вывода
 //       file_energy_dep.close();
}

void ExG4DetectorConstruction01::DefineCommands()
{
  // Define /B5/detector command directory using generic messenger class
  fMessenger = new G4GenericMessenger(this, 
                                      "/B5/detector/", 
                                      "Detector control");

  // targetAngle command
  auto& targetAngleCmd
    = fMessenger->DeclareMethodWithUnit("targetAngle","deg",
                                &ExG4DetectorConstruction01::SetTargetAngle, 
                                "Set rotation angle of the second arm.");
  targetAngleCmd.SetParameterName("angle", true);
  //armAngleCmd.SetRange("angle>=0. && angle<180.");
  targetAngleCmd.SetDefaultValue("30.");
    
}


