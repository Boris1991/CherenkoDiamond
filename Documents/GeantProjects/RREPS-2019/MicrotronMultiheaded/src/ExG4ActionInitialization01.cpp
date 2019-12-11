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
// $Id: B1ActionInitialization.cc 68058 2013-03-13 14:47:43Z gcosmo $
//
/// \file ExG4ActionInitialization01.cpp
/// \brief Implementation of the ExG4ActionInitialization01 class

//Создано специально для проекта http://dev.asifmoda.com/geant4
//Сообщество в facebook  https://www.facebook.com/groups/248240199204054/

#include "ExG4ActionInitialization01.hh"
#include "ExG4PrimaryGeneratorAction01.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
/// Обязательный класс, который должен быть объявлен в проекте Geant4
/// Имя класса может быть другим, и он долже наследоваться от
/// класса G4VUserActionInitialization
/// Конструктор
ExG4ActionInitialization01::ExG4ActionInitialization01()
    : G4VUserActionInitialization()
{}

//Деструктор
ExG4ActionInitialization01::~ExG4ActionInitialization01()
{}
//Создание начального источника частиц и покока моделирования
void ExG4ActionInitialization01::Build() const
{
    SetUserAction(new ExG4PrimaryGeneratorAction01);//Задается начальный источник частиц
    // через обязательный класс ExG4PrimaryGeneratorAction01
    //Создание потока
    RunAction* runAction = new RunAction;
    //Регистрация потока
    SetUserAction(runAction);
    //В EventAction запускается 1 частица
    EventAction* eventAction = new EventAction(runAction);
    //Регистрируем
    SetUserAction(eventAction);
    //Так же создаем и регистрируем класс для получения происходящих событий
    //при моделировании
    SetUserAction(new SteppingAction(eventAction));
}
//Создание главного потока
void ExG4ActionInitialization01::BuildForMaster() const {
    //Просто создаем и регистрируем поток
    RunAction* runAction = new RunAction;
    SetUserAction(runAction);
}
