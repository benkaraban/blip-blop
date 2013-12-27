# Microsoft Developer Studio Project File - Name="MyDX" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MyDX - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BB3.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BB3.mak" CFG="MyDX - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MyDX - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MyDX - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MyDX - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ddraw.lib dinput.lib dxguid.lib winmm.lib dsound.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"Release/BlipBlop.exe"

!ELSEIF  "$(CFG)" == "MyDX - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /Zd /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MyDX - Win32 Release"
# Name "MyDX - Win32 Debug"
# Begin Group "Libs"

# PROP Default_Filter ".lib"
# Begin Source File

SOURCE=.\fmodvc.lib
# End Source File
# End Group
# Begin Group "Headers"

# PROP Default_Filter ".h"
# Begin Source File

SOURCE=.\AlphaBlend.h
# End Source File
# Begin Source File

SOURCE=.\BenDebug.h
# End Source File
# Begin Source File

SOURCE=.\bendivers.h
# End Source File
# Begin Source File

SOURCE=.\BenMaths.h
# End Source File
# Begin Source File

SOURCE=.\Blip.h
# End Source File
# Begin Source File

SOURCE=.\Blop.h
# End Source File
# Begin Source File

SOURCE=.\Bonus.h
# End Source File
# Begin Source File

SOURCE=.\BonusBeer.h
# End Source File
# Begin Source File

SOURCE=.\BonusFusil.h
# End Source File
# Begin Source File

SOURCE=.\BonusInvincible.h
# End Source File
# Begin Source File

SOURCE=.\BonusLaser.h
# End Source File
# Begin Source File

SOURCE=.\BonusLF.h
# End Source File
# Begin Source File

SOURCE=.\BonusPM.h
# End Source File
# Begin Source File

SOURCE=.\BonusTonneau.h
# End Source File
# Begin Source File

SOURCE=.\BonusVache.h
# End Source File
# Begin Source File

SOURCE=.\Bulle.h
# End Source File
# Begin Source File

SOURCE=.\CINEPlayer.h
# End Source File
# Begin Source File

SOURCE=.\Config.h
# End Source File
# Begin Source File

SOURCE=.\ControlAlias.h
# End Source File
# Begin Source File

SOURCE=.\Controlor.h
# End Source File
# Begin Source File

SOURCE=.\ControlP1.h
# End Source File
# Begin Source File

SOURCE=.\ControlP2.h
# End Source File
# Begin Source File

SOURCE=.\Couille.h
# End Source File
# Begin Source File

SOURCE=.\DD_gfx.h
# End Source File
# Begin Source File

SOURCE=.\Ennemi.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiBisouAuto.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiBisouBoom.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiBisouChaman.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiBisouCiel.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiBisouCoeur.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiBisouEtoile.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiBisouJedi.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiBisouNuage.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiBisouSIB.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiBisouZombi.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiBulbizarre.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiBulbizarreHeros.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiCOM.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiComHeros.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiComVolant.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiDiabolo.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiFlameche.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiFlamecheHeros.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiGrandSmurf.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiKnukles.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiLara.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiLemmings.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiLemmingsVolant.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiLuigi.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiMario.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiMarioHologramme.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiMariotapette.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiPacman.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiPic.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiPikachu.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiPikashuHeros.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiPoid.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiPrincesse.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiPrincesseguard.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiRayman.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiSmurf.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiSmurfALunettes.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiSmurfCigogne.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiSmurfCoquet.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiSmurfCostaud.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiSmurfette.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiSmurfFarceur.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiSmurfFrileux.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiSmurfGourmand.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiSmurfParesseux.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiSmurfPaysan.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiSmurfPeon.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiSmurfSauvage.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiSnorkBase1.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiSnorkInBlack.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiSnorkInBlackBoss.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiSnorkyBase1.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiSnorkyBase2.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiSnorkyGouverneur.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiSnorkyHyporider.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiSnorkyMage.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiSonic.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiTails.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiTailsvolant.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiTete_Rayman.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiToad.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiVoiturePacman.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiYoshi.h
# End Source File
# Begin Source File

SOURCE=.\EnnemiYoshiDCA.h
# End Source File
# Begin Source File

SOURCE=.\Event.h
# End Source File
# Begin Source File

SOURCE=.\EventBonus.h
# End Source File
# Begin Source File

SOURCE=.\EventEnnemi.h
# End Source File
# Begin Source File

SOURCE=.\EventFondAnime.h
# End Source File
# Begin Source File

SOURCE=.\EventGenBonus.h
# End Source File
# Begin Source File

SOURCE=.\EventGenEnnemi.h
# End Source File
# Begin Source File

SOURCE=.\EventHoldFire.h
# End Source File
# Begin Source File

SOURCE=.\EventLock.h
# End Source File
# Begin Source File

SOURCE=.\EventMeteo.h
# End Source File
# Begin Source File

SOURCE=.\EventMiFond.h
# End Source File
# Begin Source File

SOURCE=.\EventMusic.h
# End Source File
# Begin Source File

SOURCE=.\EventPremierPlan.h
# End Source File
# Begin Source File

SOURCE=.\EventRPG.h
# End Source File
# Begin Source File

SOURCE=.\EventScrollSpeed.h
# End Source File
# Begin Source File

SOURCE=.\EventSetFlag.h
# End Source File
# Begin Source File

SOURCE=.\EventSon.h
# End Source File
# Begin Source File

SOURCE=.\EventTexte.h
# End Source File
# Begin Source File

SOURCE=.\EventVehicule.h
# End Source File
# Begin Source File

SOURCE=.\Explosion.h
# End Source File
# Begin Source File

SOURCE=.\FicEvents.h
# End Source File
# Begin Source File

SOURCE=.\fmod.h
# End Source File
# Begin Source File

SOURCE=".\Fond PokeCaissePlateforme.h"
# End Source File
# Begin Source File

SOURCE=.\FondAssembleur.h
# End Source File
# Begin Source File

SOURCE=.\FondBattleCruiser.h
# End Source File
# Begin Source File

SOURCE=.\FondBombe.h
# End Source File
# Begin Source File

SOURCE=.\FondBossventilo.h
# End Source File
# Begin Source File

SOURCE=.\FondCube.h
# End Source File
# Begin Source File

SOURCE=.\FondDos.h
# End Source File
# Begin Source File

SOURCE=.\FondDrapeau.h
# End Source File
# Begin Source File

SOURCE=.\FondEau.h
# End Source File
# Begin Source File

SOURCE=.\FondEcrancamera.h
# End Source File
# Begin Source File

SOURCE=.\FondEcraneige.h
# End Source File
# Begin Source File

SOURCE=.\FondElectronics.h
# End Source File
# Begin Source File

SOURCE=.\FondEtoile.h
# End Source File
# Begin Source File

SOURCE=.\FondLampe2.h
# End Source File
# Begin Source File

SOURCE=.\FondLCD.h
# End Source File
# Begin Source File

SOURCE=.\FondLumiere.h
# End Source File
# Begin Source File

SOURCE=.\FondMonolite.h
# End Source File
# Begin Source File

SOURCE=.\FondPiece.h
# End Source File
# Begin Source File

SOURCE=.\FondPoissons.h
# End Source File
# Begin Source File

SOURCE=.\FondPokeAlarme1.h
# End Source File
# Begin Source File

SOURCE=.\FondPokeAscenceur.h
# End Source File
# Begin Source File

SOURCE=.\FondPokeAscenseur2.h
# End Source File
# Begin Source File

SOURCE=.\FondPokeCaisse.h
# End Source File
# Begin Source File

SOURCE=.\FondPokeCaissePlateforme2.h
# End Source File
# Begin Source File

SOURCE=.\FondPokeCaisseTombante.h
# End Source File
# Begin Source File

SOURCE=.\FondPokeCiel.h
# End Source File
# Begin Source File

SOURCE=.\FondPokeFleche.h
# End Source File
# Begin Source File

SOURCE=.\FondPokeInterupteur.h
# End Source File
# Begin Source File

SOURCE=.\FondPokeLevel2.h
# End Source File
# Begin Source File

SOURCE=.\FondPokeLevel3.h
# End Source File
# Begin Source File

SOURCE=.\FondRing.h
# End Source File
# Begin Source File

SOURCE=.\FondRocher1.h
# End Source File
# Begin Source File

SOURCE=.\FondRocher2.h
# End Source File
# Begin Source File

SOURCE=.\FondRocherHyperspace.h
# End Source File
# Begin Source File

SOURCE=.\FondSnorkSas.h
# End Source File
# Begin Source File

SOURCE=.\FondStatique.h
# End Source File
# Begin Source File

SOURCE=.\FondTest.h
# End Source File
# Begin Source File

SOURCE=.\FondTirCruiser.h
# End Source File
# Begin Source File

SOURCE=.\FondTournesol1.h
# End Source File
# Begin Source File

SOURCE=.\FondTournesol2.h
# End Source File
# Begin Source File

SOURCE=.\FondTournesol3.h
# End Source File
# Begin Source File

SOURCE=.\FondTournesol4.h
# End Source File
# Begin Source File

SOURCE=.\FondVentilo.h
# End Source File
# Begin Source File

SOURCE=.\FondWindows.h
# End Source File
# Begin Source File

SOURCE=.\FondWorldmap.h
# End Source File
# Begin Source File

SOURCE=.\Fonte.h
# End Source File
# Begin Source File

SOURCE=.\Game.h
# End Source File
# Begin Source File

SOURCE=.\GenBonus.h
# End Source File
# Begin Source File

SOURCE=.\GenEnnemi.h
# End Source File
# Begin Source File

SOURCE=.\GenEnnemiTMP.h
# End Source File
# Begin Source File

SOURCE=.\Giclure.h
# End Source File
# Begin Source File

SOURCE=.\Globals.h
# End Source File
# Begin Source File

SOURCE=.\GoreBisouAuto.h
# End Source File
# Begin Source File

SOURCE=.\GoreBisouBoom.h
# End Source File
# Begin Source File

SOURCE=.\GoreGiclure.h
# End Source File
# Begin Source File

SOURCE=.\GorePiedBisouZombi.h
# End Source File
# Begin Source File

SOURCE=.\GorePiedsBisouCiel.h
# End Source File
# Begin Source File

SOURCE=.\GorePiedsBisouEtoile.h
# End Source File
# Begin Source File

SOURCE=.\GoreTeteBisouCoeur.h
# End Source File
# Begin Source File

SOURCE=.\HiScores.h
# End Source File
# Begin Source File

SOURCE=.\ImpactLaser.h
# End Source File
# Begin Source File

SOURCE=.\Input.h
# End Source File
# Begin Source File

SOURCE=.\Joueur.h
# End Source File
# Begin Source File

SOURCE=.\KeyTranslator.h
# End Source File
# Begin Source File

SOURCE=.\LGXpacker.h
# End Source File
# Begin Source File

SOURCE=.\LTimer.h
# End Source File
# Begin Source File

SOURCE=.\MakeBonus.h
# End Source File
# Begin Source File

SOURCE=.\MenuGame.h
# End Source File
# Begin Source File

SOURCE=.\MenuMain.h
# End Source File
# Begin Source File

SOURCE=.\MeteoNeige.h
# End Source File
# Begin Source File

SOURCE=.\MeteoPluie.h
# End Source File
# Begin Source File

SOURCE=.\MorceauRayman.h
# End Source File
# Begin Source File

SOURCE=.\MorceauSonicRing.h
# End Source File
# Begin Source File

SOURCE=.\MorceauTeteRayman.h
# End Source File
# Begin Source File

SOURCE=.\MorceauxTeteSnorky.h
# End Source File
# Begin Source File

SOURCE=.\MusicBank.h
# End Source File
# Begin Source File

SOURCE=.\Personnage.h
# End Source File
# Begin Source File

SOURCE=.\Picture.h
# End Source File
# Begin Source File

SOURCE=.\PictureBank.h
# End Source File
# Begin Source File

SOURCE=.\PPlanTest.h
# End Source File
# Begin Source File

SOURCE=.\Precache.h
# End Source File
# Begin Source File

SOURCE=.\Restore.h
# End Source File
# Begin Source File

SOURCE=.\RPGPlayer.h
# End Source File
# Begin Source File

SOURCE=.\Scroll.h
# End Source File
# Begin Source File

SOURCE=.\Sound.h
# End Source File
# Begin Source File

SOURCE=.\SoundBank.h
# End Source File
# Begin Source File

SOURCE=.\SoundBankBB.h
# End Source File
# Begin Source File

SOURCE=.\Sprite.h
# End Source File
# Begin Source File

SOURCE=.\Stdafx.h
# End Source File
# Begin Source File

SOURCE=.\SuperListe.h
# End Source File
# Begin Source File

SOURCE=.\TexteCool.h
# End Source File
# Begin Source File

SOURCE=.\Tir.h
# End Source File
# Begin Source File

SOURCE=.\TirArcCiel.h
# End Source File
# Begin Source File

SOURCE=.\TirBB.h
# End Source File
# Begin Source File

SOURCE=.\TirBBFusil.h
# End Source File
# Begin Source File

SOURCE=.\TirBBLaser.h
# End Source File
# Begin Source File

SOURCE=.\TirBBLF.h
# End Source File
# Begin Source File

SOURCE=.\TirBBM16.h
# End Source File
# Begin Source File

SOURCE=.\TirBBPM.h
# End Source File
# Begin Source File

SOURCE=.\TirBBVache.h
# End Source File
# Begin Source File

SOURCE=.\TirBisouMortel.h
# End Source File
# Begin Source File

SOURCE=.\TirBouleChaman.h
# End Source File
# Begin Source File

SOURCE=.\TirCadeau.h
# End Source File
# Begin Source File

SOURCE=.\TirCarapace.h
# End Source File
# Begin Source File

SOURCE=.\TirCoeurBisou.h
# End Source File
# Begin Source File

SOURCE=.\TirColonneChaman.h
# End Source File
# Begin Source File

SOURCE=.\TirCruiserLaser.h
# End Source File
# Begin Source File

SOURCE=.\TirDeboucheChiote.h
# End Source File
# Begin Source File

SOURCE=.\TirEpeeLaser.h
# End Source File
# Begin Source File

SOURCE=.\TirEpine.h
# End Source File
# Begin Source File

SOURCE=.\TirEtoile.h
# End Source File
# Begin Source File

SOURCE=.\TirGateau.h
# End Source File
# Begin Source File

SOURCE=.\TirHadoken.h
# End Source File
# Begin Source File

SOURCE=.\TirMarioFireball.h
# End Source File
# Begin Source File

SOURCE=.\TirMarioFireballVertical.h
# End Source File
# Begin Source File

SOURCE=.\TirNuage.h
# End Source File
# Begin Source File

SOURCE=.\TirRaymanPoing.h
# End Source File
# Begin Source File

SOURCE=.\TirSmurfSauvage.h
# End Source File
# Begin Source File

SOURCE=.\TirSnorkybase.h
# End Source File
# Begin Source File

SOURCE=.\TirSnorkyBase2.h
# End Source File
# Begin Source File

SOURCE=.\TirSnorkyGouverneur.h
# End Source File
# Begin Source File

SOURCE=.\TirSnorkyMage.h
# End Source File
# Begin Source File

SOURCE=.\TirSoniceclair.h
# End Source File
# Begin Source File

SOURCE=.\TirTornade.h
# End Source File
# Begin Source File

SOURCE=.\trace.h
# End Source File
# Begin Source File

SOURCE=.\TxtData.h
# End Source File
# Begin Source File

SOURCE=.\Vehicule.h
# End Source File
# Begin Source File

SOURCE=.\VehiculeHypo.h
# End Source File
# Begin Source File

SOURCE=.\VehiculeTestTourelle.h
# End Source File
# Begin Source File

SOURCE=.\VehivuleCigogne.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\AlphaBlend.cpp
# End Source File
# Begin Source File

SOURCE=.\BenDebug.cpp
# End Source File
# Begin Source File

SOURCE=.\BenDivers.cpp
# End Source File
# Begin Source File

SOURCE=.\BenMaths.cpp
# End Source File
# Begin Source File

SOURCE=".\Blip'n Blop 3.cpp"
# End Source File
# Begin Source File

SOURCE=.\Blip.cpp
# End Source File
# Begin Source File

SOURCE=.\Bulle.cpp
# End Source File
# Begin Source File

SOURCE=.\CINEPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\Config.cpp
# End Source File
# Begin Source File

SOURCE=.\Couille.cpp
# End Source File
# Begin Source File

SOURCE=.\DD_gfx.cpp
# End Source File
# Begin Source File

SOURCE=.\Ennemi.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiBisouAuto.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiBisouBoom.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiBisouChaman.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiBisouCiel.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiBisouCoeur.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiBisouEtoile.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiBisouJedi.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiBisouNuage.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiBisouSIB.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiBisouZombi.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiBulbizarre.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiBulbizarreHeros.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiCOM.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiComHeros.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiCOMVolant.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiDiabolo.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiFlameche.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiFlamecheHeros.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiGrandSmurf.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiKnukles.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiLara.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiLemmings.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiLuigi.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiMario.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiMarioHologramme.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiMariotapette.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiPacman.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiPic.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiPikachu.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiPikashuHeros.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiPoid.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiPrincesse.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiPrincesseguard.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiRayman.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiSmurf.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiSmurfCigogne.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiSmurfCostaud.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiSmurfette.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiSmurfFarceur.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiSmurfGourmand.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiSmurfPaysan.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiSmurfSauvage.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiSnorkInBlack.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiSnorkInBlackBoss.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiSnorkyBase2.cpp
# End Source File
# Begin Source File

SOURCE=.\ennemiSnorkyGouverneur.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiSnorkyHyporider.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiSnorkyMage.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiSonic.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiSorkyBase1.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiTails.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiTailsvolant.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiTeteRayman.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiToad.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiVoiturePacman.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiYoshi.cpp
# End Source File
# Begin Source File

SOURCE=.\EnnemiYoshiDCA.cpp
# End Source File
# Begin Source File

SOURCE=.\EventBonus.cpp
# End Source File
# Begin Source File

SOURCE=.\EventEnnemi.cpp
# End Source File
# Begin Source File

SOURCE=.\EventFondAnime.cpp
# End Source File
# Begin Source File

SOURCE=.\EventGenEnnemi.cpp
# End Source File
# Begin Source File

SOURCE=.\EventLock.cpp
# End Source File
# Begin Source File

SOURCE=.\EventMiFond.cpp
# End Source File
# Begin Source File

SOURCE=.\EventMusic.cpp
# End Source File
# Begin Source File

SOURCE=.\EventPremierPlan.cpp
# End Source File
# Begin Source File

SOURCE=.\EventVehicule.cpp
# End Source File
# Begin Source File

SOURCE=.\Explosion.cpp
# End Source File
# Begin Source File

SOURCE=.\FondAssembleur.cpp
# End Source File
# Begin Source File

SOURCE=.\FondBattleCruiser.cpp
# End Source File
# Begin Source File

SOURCE=.\FondBombe.cpp
# End Source File
# Begin Source File

SOURCE=.\FondBossventilo.cpp
# End Source File
# Begin Source File

SOURCE=.\FondCube.cpp
# End Source File
# Begin Source File

SOURCE=.\FondEcrancamera.cpp
# End Source File
# Begin Source File

SOURCE=.\FondElectronics.cpp
# End Source File
# Begin Source File

SOURCE=.\FondEtoile.cpp
# End Source File
# Begin Source File

SOURCE=.\FondLampe2.cpp
# End Source File
# Begin Source File

SOURCE=.\FondLCD.cpp
# End Source File
# Begin Source File

SOURCE=.\FondLumiere.cpp
# End Source File
# Begin Source File

SOURCE=.\FondMonolite.cpp
# End Source File
# Begin Source File

SOURCE=.\FondPiece.cpp
# End Source File
# Begin Source File

SOURCE=.\FondPoissons.cpp
# End Source File
# Begin Source File

SOURCE=.\FondPokeAscenceur.cpp
# End Source File
# Begin Source File

SOURCE=.\FondPokeAscenseur2.cpp
# End Source File
# Begin Source File

SOURCE=.\FondPokeCaisse.cpp
# End Source File
# Begin Source File

SOURCE=.\FondPokeCaissePlateforme.cpp
# End Source File
# Begin Source File

SOURCE=.\FondPokeCaissePlateforme2.cpp
# End Source File
# Begin Source File

SOURCE=.\FondPokeCaisseTombante.cpp
# End Source File
# Begin Source File

SOURCE=.\FondPokeCiel.cpp
# End Source File
# Begin Source File

SOURCE=.\FondPokeInterupteur.cpp
# End Source File
# Begin Source File

SOURCE=.\FondPokeLevel2.cpp
# End Source File
# Begin Source File

SOURCE=.\FondPokeLevel3.cpp
# End Source File
# Begin Source File

SOURCE=.\FondRing.cpp
# End Source File
# Begin Source File

SOURCE=.\FondRocher1.cpp
# End Source File
# Begin Source File

SOURCE=.\fondRocher2.cpp
# End Source File
# Begin Source File

SOURCE=.\FondRocherHyperspace.cpp
# End Source File
# Begin Source File

SOURCE=.\FondSnorkSas.cpp
# End Source File
# Begin Source File

SOURCE=.\FondTircruiser.cpp
# End Source File
# Begin Source File

SOURCE=.\FondWorldmap.cpp
# End Source File
# Begin Source File

SOURCE=.\Fonte.cpp
# End Source File
# Begin Source File

SOURCE=.\Game.cpp
# End Source File
# Begin Source File

SOURCE=.\GenBonus.cpp
# End Source File
# Begin Source File

SOURCE=.\GenEnnemi.cpp
# End Source File
# Begin Source File

SOURCE=.\GenEnnemiTMP.cpp
# End Source File
# Begin Source File

SOURCE=.\Giclure.cpp
# End Source File
# Begin Source File

SOURCE=.\Globals.cpp
# End Source File
# Begin Source File

SOURCE=.\GoreGiclure.cpp
# End Source File
# Begin Source File

SOURCE=.\HiScores.cpp
# End Source File
# Begin Source File

SOURCE=.\Input.cpp
# End Source File
# Begin Source File

SOURCE=.\KeyTranslator.cpp
# End Source File
# Begin Source File

SOURCE=.\LGXpacker.cpp
# End Source File
# Begin Source File

SOURCE=.\LTimer.cpp
# End Source File
# Begin Source File

SOURCE=.\MakeBonus.cpp
# End Source File
# Begin Source File

SOURCE=.\MenuGame.cpp
# End Source File
# Begin Source File

SOURCE=.\MenuMain.cpp
# End Source File
# Begin Source File

SOURCE=.\MeteoNeige.cpp
# End Source File
# Begin Source File

SOURCE=.\MeteoPluie.cpp
# End Source File
# Begin Source File

SOURCE=.\MoceauxTeteSnorky.cpp
# End Source File
# Begin Source File

SOURCE=.\MorceauRayman.cpp
# End Source File
# Begin Source File

SOURCE=.\MorceauSonicRing.cpp
# End Source File
# Begin Source File

SOURCE=.\MorceauTeteRayman.cpp
# End Source File
# Begin Source File

SOURCE=.\MusicBank.cpp
# End Source File
# Begin Source File

SOURCE=.\Personnage.cpp
# End Source File
# Begin Source File

SOURCE=.\Picture.cpp
# End Source File
# Begin Source File

SOURCE=.\PictureBank.cpp
# End Source File
# Begin Source File

SOURCE=.\Restore.cpp
# End Source File
# Begin Source File

SOURCE=.\RPGPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\Scroll.cpp
# End Source File
# Begin Source File

SOURCE=.\Sound.cpp
# End Source File
# Begin Source File

SOURCE=.\SoundBank.cpp
# End Source File
# Begin Source File

SOURCE=.\SoundBankBB.cpp
# End Source File
# Begin Source File

SOURCE=.\Sprite.cpp
# End Source File
# Begin Source File

SOURCE=.\SuperListe.cpp
# End Source File
# Begin Source File

SOURCE=.\TexteCool.cpp
# End Source File
# Begin Source File

SOURCE=.\TirBB.cpp
# End Source File
# Begin Source File

SOURCE=.\TirBBFusil.cpp
# End Source File
# Begin Source File

SOURCE=.\TirBBLaser.cpp
# End Source File
# Begin Source File

SOURCE=.\TirBBLF.cpp
# End Source File
# Begin Source File

SOURCE=.\TirBBM16.cpp
# End Source File
# Begin Source File

SOURCE=.\TirBBPM.cpp
# End Source File
# Begin Source File

SOURCE=.\TirBBVache.cpp
# End Source File
# Begin Source File

SOURCE=.\TirBouleChaman.cpp
# End Source File
# Begin Source File

SOURCE=.\TirCadeau.cpp
# End Source File
# Begin Source File

SOURCE=.\TirCarapace.cpp
# End Source File
# Begin Source File

SOURCE=.\TirCoeurBisou.cpp
# End Source File
# Begin Source File

SOURCE=.\TirColonneChaman.cpp
# End Source File
# Begin Source File

SOURCE=.\TirCruiserLaser.cpp
# End Source File
# Begin Source File

SOURCE=.\TirDeboucheChiote.cpp
# End Source File
# Begin Source File

SOURCE=.\TirEpeeLaser.cpp
# End Source File
# Begin Source File

SOURCE=.\TirEpine.cpp
# End Source File
# Begin Source File

SOURCE=.\TirGateau.cpp
# End Source File
# Begin Source File

SOURCE=.\TirMarioFireball.cpp
# End Source File
# Begin Source File

SOURCE=.\TirMarioFireballVertical.cpp
# End Source File
# Begin Source File

SOURCE=.\TirNuage.cpp
# End Source File
# Begin Source File

SOURCE=.\TirRaymanPoing.cpp
# End Source File
# Begin Source File

SOURCE=.\TirSmurfSauvage.cpp
# End Source File
# Begin Source File

SOURCE=.\TirSnorkyBase.cpp
# End Source File
# Begin Source File

SOURCE=.\TirSnorkyBase2.cpp
# End Source File
# Begin Source File

SOURCE=.\TirSnorkyGouverneur.cpp
# End Source File
# Begin Source File

SOURCE=.\TirSnorkyMage.cpp
# End Source File
# Begin Source File

SOURCE=.\TirSoniceclair.cpp
# End Source File
# Begin Source File

SOURCE=.\TirTornade.cpp
# End Source File
# Begin Source File

SOURCE=.\TxtData.cpp
# End Source File
# Begin Source File

SOURCE=.\Vehicule.cpp
# End Source File
# Begin Source File

SOURCE=.\VehiculeCigogne.cpp
# End Source File
# Begin Source File

SOURCE=.\VehiculeHypo.cpp
# End Source File
# End Target
# End Project
