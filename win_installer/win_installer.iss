;==============================================================================
; Script initializes setup wizard, which checks whether DirectX 9.0c and MSVC 
; Redist 2012 are present. If not, appropriate files are extracted to the 
; temporary directory and installers are started. In addition, system version 
; (32b/64b) is considered. All installers are built in the .exe file.
; According to official sources 'c' version of DirectX 9.0 includes following
; registry version entries: 4.09.00.0903 and 4.09.00.0904.
; In addition, script introduces a feature, which search all files starting 
; with 'd3dx9' sequence (upper/lower case combinations considered). It prevents 
; the situation when registry entry is correct but there are no files related
; to DirectX 9.0.
;==============================================================================
; author: dybisz
;------------------------------------------------------------------------------

[Setup]
AppName=Dybisz Bachelor Thesis
AppVersion=1.0
DefaultDirName={pf}\Dybisz Bachelor Thesis
DefaultGroupName=Dybisz Bachelor Thesis
UninstallDisplayIcon={app}\bachelor_water.exe
Compression=lzma2
SolidCompression=yes
SetupIconFile="..\res\icon.ico"

[Files]
Source: "..\bachelor_water.exe"; DestDir: "{app}"; Flags: replacesameversion
Source: "..\res\*"; DestDir: "{app}\res\"; Flags: replacesameversion recursesubdirs
Source: "..\config.ini"; DestDir: "{app}"; Flags: replacesameversion
Source: "..\PhysX3_x86.dll"; DestDir: "{app}"; Flags: replacesameversion
Source: "..\PhysX3Common_x86.dll"; DestDir: "{app}"; Flags: replacesameversion
Source: "redist\vc_redist.x64.exe"; DestDir: "{app}\redist"
Source: "redist\vc_redist.x86.exe"; DestDir: "{app}\redist"
Source: "res\mark_confirm.bmp";Flags: dontcopy
Source: "res\mark_not_confirm.bmp"; Flags: dontcopy

[Icons]
Name: "{group}\Dybisz Bachelor Thesis"; Filename: "{app}\bachelor_water.exe"  ; IconFileName: "{app}\res\icon.ico"


[Code]
//==============================================================================
// Unicode / ASCI Version Check
//------------------------------------------------------------------------------
#IFDEF UNICODE
  #DEFINE AW "W"
#ELSE
  #DEFINE AW "A"
#ENDIF

//==============================================================================
// MSVC Detection Constants
//------------------------------------------------------------------------------
const
  INSTALLSTATE_DEFAULT        = 5;  

  VC_2012_REDIST_MIN_UPD4_X86 = '{BD95A8CD-1D9F-35AD-981A-3E7925026EBB}';
  VC_2012_REDIST_MIN_UPD4_X64 = '{CF2BEA3C-26EA-32F8-AA9B-331F7E34BA97}';
  VC_2012_REDIST_ADD_UPD4_X86 = '{B175520C-86A2-35A7-8619-86DC379688B9}';
  VC_2012_REDIST_ADD_UPD4_X64 = '{37B8F9C7-03FB-3253-8781-2517C99D7C00}';

  VC_2015_REDIST_X86_MIN = '{A2563E55-3BEC-3828-8D67-E5E8B9E8B675}';
  VC_2015_REDIST_X64_MIN = '{0D3E9E15-DE7A-300B-96F1-B4AF12B96488}';
  VC_2015_REDIST_X86_ADD = '{BE960C1C-7BAD-3DE6-8B1A-2616FE532845}';
  VC_2015_REDIST_X64_ADD = '{BC958BD2-5DAC-3862-BB1A-C1BE0790438D}';
//==============================================================================
// Global Variables 
//------------------------------------------------------------------------------
var
  gMSVCMissing    : Boolean;
  g64BitOS        : Boolean;

//==============================================================================
// Auxiliary Procedures and Functions
//------------------------------------------------------------------------------

// Standard procedure of initializing global variables.
// Only place to set they default values.
procedure InitializeGlobals;
begin
  gMSVCMissing    := true;
  g64BitOS        := false;
end;

// Checks status of product with provided id.
// List of MSVC's ids is located at top of the [Code] section. 
function MsiQueryProductState(szProduct: string): Integer; 
  external 'MsiQueryProductState{#AW}@msi.dll stdcall';

// Checks if MSVC of a given ID is installed. Identifiers are
// listed at top of the [Code] part, withing global variables 
// section.
//
// @param  ProductID Identification string for particular MSVC 
//         distribution.
// @return Is product installed?
function VCVersionInstalled(const ProductID: string): Boolean;
begin
  Result := MsiQueryProductState(ProductID) = INSTALLSTATE_DEFAULT;
end;

// Determine whether MSVC 2015 Redistr is installed or not. Operating 
// system version (32/64 bit) is taken into account. 
//
// NOTE: function sets gMSVCMissing to either true or false - depending
// on the result;
//
// @return True when MSVC 2015 Redist needs to be installed, 
//         otherwise false.
function MSVCNeedsInstalling() : Boolean;
begin
  if IsWin64 then
    begin
      gMSVCMissing := not (VCVersionInstalled(VC_2015_REDIST_X86_ADD));
      Result := gMSVCMissing;
    end
  else
    begin
      gMSVCMissing := not (VCVersionInstalled(VC_2015_REDIST_X86_ADD));
      Result := gMSVCMissing;
    end;
end;

// NOTE: function sets gMSVCMissing to either true or false - depending
// on the result;
//
// @return String object with path to the correct marker - depending on
//         MSVC's version compatibility.
function LoadAppropriateMSVCMarkerBitmap : String;
begin
  if(MSVCNeedsInstalling()) then
    begin
      Result := ExpandConstant('{tmp}\mark_not_confirm.bmp');
    end
  else
    begin
      Result := ExpandConstant('{tmp}\mark_confirm.bmp');
    end;
end;

// Is the system 32 or 64 bit? Method created just to encapsulate calls
// of builded IsWin64 function resulting in determining the string.
// 
// @return Either '32bit' or '64bit' String object.
function GetOSVersion(): String;
var
  sVersion : String;
begin
  sVersion := '32bit';
  if IsWin64 then
    begin
      sVersion := '64bit';
      g64BitOS := true;
    end;
  Result := sVersion;
end;

// Runs installer provided as the function's argument. Obvious errors are 
// processed and appropriate message box is created in case of any errors.
//
// @param ExecutablePath Relative path to the executable file with installer.
procedure InstallMissingDependency(ExecutablePath : String);
var
  InstallerResult : Integer;
begin
  ExtractTemporaryFile(ExecutablePath);
  if not Exec(ExpandConstant('{tmp}\' + ExecutablePath), '', '', SW_SHOW, ewWaitUntilTerminated, InstallerResult) then
    begin
      MsgBox('Error occured during ' + ExecutablePath + ' installer.', mbError, mb_Ok);
    end;
end;

// Installer assumes that if any dependencies are missing, they will be installed
// after main installation will terminate. Following callback function assures
// that MSVC installer (when needed) will be called.
//
// @param CurStep Indicates progress in the installation process.
procedure CurStepChanged(CurStep: TSetupStep);
begin
  if CurStep = ssPostInstall then
    begin
      if(gMSVCMissing and g64BitOS) then
        InstallMissingDependency('vc_redist.x64.exe');
        InstallMissingDependency('vc_redist.x86.exe');
      if(gMSVCMissing and (not g64BitOS)) then
        InstallMissingDependency('vc_redist.x86.exe');
    end; 
end;

//==============================================================================
// Initialize Pages
//------------------------------------------------------------------------------

procedure CreateDependenciesPage;
var
  Page                          : TWizardPage;
  MSVCCurrentVersion            : TNewStaticText; 
  OSCurrentVersion              : TNewStaticText;
  MissingDependencies           : TLabel;
  MSVCMarkName                  : String;
  MSVCConfirmationMarkBitmap    : TBitmapImage;
  Spacing                       : Integer;
begin  
  Page := CreateCustomPage(wpWelcome, 'Dependencies', 'Wizard will check if MSVC Redist 2015 is present in the system,'+
                                       'provide it when needed and install the application.');
  Spacing := 8;

  (* ----- MSVC Check ----- *)
  MSVCCurrentVersion          := TNewStaticText.Create(Page);
  MSVCCurrentVersion.Top      := ScaleY(Spacing);
  MSVCCurrentVersion.Caption  := 'MSVC 2015 Redist: ';
  MSVCCurrentVersion.AutoSize := True;
  MSVCCurrentVersion.Parent   := Page.Surface;

  MSVCMarkName := LoadAppropriateMSVCMarkerBitmap(); 
  ExtractTemporaryFile(ExtractFileName(MSVCMarkName));

  MSVCConfirmationMarkBitmap        := TBitmapImage.Create(Page);
  MSVCConfirmationMarkBitmap.Bitmap.LoadFromFile(MSVCMarkName);
  MSVCConfirmationMarkBitmap.Left   := MSVCCurrentVersion.Width + ScaleX(5);
  MSVCConfirmationMarkBitmap.Top    := MSVCCurrentVersion.Top + 2;
  MSVCConfirmationMarkBitmap.Height := MSVCConfirmationMarkBitmap.Height/10;
  MSVCConfirmationMarkBitmap.Width  := MSVCConfirmationMarkBitmap.Width/10;
  MSVCConfirmationMarkBitmap.Parent := Page.Surface;

  (* ----- OS Check ----- *)
  OSCurrentVersion := TNewStaticText.Create(Page);
  OSCurrentVersion.Top := MSVCCurrentVersion.Top + MSVCCurrentVersion.Height + ScaleY(Spacing);
  OSCurrentVersion.Caption := 'OS version:              ' + GetOSVersion();
  OSCurrentVersion.AutoSize := True;
  OSCurrentVersion.Parent := Page.Surface;

  (* ----- Missing Components Warning ----- *)
  if(gMSVCMissing) then
    begin
      MissingDependencies            := TLabel.Create(Page);
      MissingDependencies.Top        := Page.SurfaceHeight - 70 //OSCurrentVersion.Top + OSCurrentVersion.Height + ScaleY(106);
      MissingDependencies.Caption    := 'WARNING: Some dependencies are missing.' +
                                        ' Appropriate setups will run after following installation proces will finish.' +
                                        ' One can simply cancel them if manual installation is preferred.';
      MissingDependencies.Font.Color := clRed;
      MissingDependencies.Width      := Page.SurfaceWidth; 
      MissingDependencies.Height     := 60;
      MissingDependencies.AutoSize   := False;
      MissingDependencies.Wordwrap   := True;
      MissingDependencies.Parent     := Page.Surface;
    end;
end;

//==============================================================================
// Setup Entry Point
//------------------------------------------------------------------------------

procedure InitializeWizard();
begin
  InitializeGlobals;
  CreateDependenciesPage;
end;