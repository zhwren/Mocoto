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
// $Id: exampleB3.cc 86065 2014-11-07 08:51:15Z gcosmo $
//
/// \file exampleB3.cc
/// \brief Main program of the B3 example
#include <time.h>
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#ifdef G4UI_USE_GAG
#include "G4UIGAG.hh"
#endif
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#ifdef G4UI_USE_XM
#include "G4UIXm.hh"
#endif


#include "MocotoDetectorConstruction.hh"
#include "MocotoPrimaryGeneratorAction.hh"
#include "MocotoPhysicsList.hh"
#include "MocotoRunAction.hh"
#include "MocotoEventAction.hh"
#include "MocotoSteppingAction.hh"
#include "MocotoAnalysisManager.hh"
#include "Randomize.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif
#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  clock_t start = clock();
  MocotoAnalysisManager* manager = MocotoAnalysisManager::getInstance();
  G4RunManager* runManager = new G4RunManager;
  runManager->SetUserInitialization(new MocotoDetectorConstruction);
  runManager->SetUserInitialization(new MocotoPhysicsList);
  runManager->SetUserAction(new MocotoPrimaryGeneratorAction);
  runManager->SetUserAction(new MocotoRunAction);
  runManager->SetUserAction(new MocotoEventAction);
  runManager->SetUserAction(new MocotoSteppingAction);
  G4String seed = argv[2];
  CLHEP::HepRandom::setTheSeed(std::atoi(seed.c_str()));
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  if (argc!=1) 
  { 
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else {
#ifdef G4VIS_USE 
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif
#ifdef G4UI_USE
      G4UIExecutive* ui = new G4UIExecutive(argc,argv);
#ifdef G4VIS_USE
      UImanager->ApplyCommand("/control/execute init_vis.mac");
#endif
      ui->SessionStart();
      delete ui;
#endif
#ifdef G4VIS_USE
  delete visManager;
#endif
  }
  manager->dispose();
  delete runManager;
  clock_t finish = clock();
  G4cout << "Total time(s):" << double(finish-start)/CLOCKS_PER_SEC << G4endl;
  return 1;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
