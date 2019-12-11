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
// $Id: B1ActionInitialization.hh 68058 2013-03-13 14:47:43Z gcosmo $
//
/// \file ExG4ActionInitialization01.hh
/// \brief Definition of the ExG4ActionInitialization01 class

//Создано специально для проекта http://dev.asifmoda.com/geant4
//Сообщество в facebook  https://www.facebook.com/groups/248240199204054/

#ifndef ExG4ActionInitialization01_h
#define ExG4ActionInitialization01_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.
/// Обязательный класс, который должен быть объявлен в проекте Geant4
/// Имя класса может быть другим, и он долже наследоваться от
/// класса G4VUserActionInitialization

class ExG4ActionInitialization01 : public G4VUserActionInitialization
{
public:
    ///Конструктор
    ExG4ActionInitialization01();
    ///Деструктор
    virtual ~ExG4ActionInitialization01();
    ///Создание вычислительного потока моделирования
    virtual void Build() const;
    ///Создание главного потока, здесь частицы не моделируются
    virtual void BuildForMaster() const;
};
#endif


