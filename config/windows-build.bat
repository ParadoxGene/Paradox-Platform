@ ECHO OFF
SETLOCAL ENABLEDELAYEDEXPANSION

FOR %%P IN (%*) DO (
    ( CALL :SetBuildCommandValue set-version build-system-version %%P)
    ( CALL :SetBuildCommandValue set-repo build-system-repo %%P)

    ( CALL :SetNextBuildCommand %%P --version set-version)
    ( CALL :SetNextBuildCommand %%P --repo set-repo)
)

SET build-dir=%~dp0..\build\build-system

IF NOT EXIST !build-dir! (
    ECHO Build System: Cloning...
    git clone --branch=!build-system-version! !build-system-repo! !build-dir!
) ELSE (
    ECHO Build System: Fetching...
    cd !build-dir! && git checkout !build-system-version! && git pull origin
)
ECHO Build System: Done
exit

:SetBuildCommandValue
    IF !next-build-command!==%~1 (
        SET next-build-command=none
        SET %~2=%~3
    )
GOTO :EOF

:SetNextBuildCommand
    IF %~1==%~2 (
        SET next-build-command=%~3
    )
GOTO :EOF