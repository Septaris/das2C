FROM mcr.microsoft.com/dotnet/framework/sdk as vcpkg_windows
SHELL ["powershell", "-Command"]

# System dependencies
RUN Invoke-Expression (New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1')
RUN choco install -y git
RUN choco install -y visualstudio2019-workload-vctools
        

# Install vcpkg
ENV VCPKG_PATH=C:\vcpkg
RUN mkdir $Env:VCPKG_PATH; \
    git clone https://github.com/Microsoft/vcpkg.git $Env:VCPKG_PATH; \
    cd $Env:VCPKG_PATH; \
    ./bootstrap-vcpkg.bat
RUN setx /M PATH $($Env:PATH + ';' + $Env:VCPKG_PATH)

FROM vcpkg_windows AS das2c_windows

# install das2c/das2py dependencies
RUN vcpkg install openssl fftw3 zlib expat pthreads --triplet x64-windows-static

# clone the das2c repository
ADD . das2c

# setup en vars for the build
ENV N_ARCH="/"
ENV DAS2C="C:/das2c"
ENV LIBRARY_INC="C:/vcpkg/installed/x64-windows-static/include"
ENV LIBRARY_LIB="C:/vcpkg/installed/x64-windows-static/lib"
ENV LIBRARY_PREFIX="C:/opt"
ENV VC_VARS_PATH="C:/Program Files (x86)/Microsoft Visual Studio/2019/BuildTools/VC/Auxiliary/Build/vcvars64.bat"


# add the invoke script used to setup the path for nmake.exe, cl.exe, etc. (x64) 
# TODO: add building tools directly to the path to avoid the setup before each nmake  
ADD docker/windows/invoke_environment.ps1 scripts/invoke_environment.ps1
WORKDIR $DAS2C
RUN . C:/scripts/invoke_environment.ps1; \
 invoke_environment $env:VC_VARS_PATH ; \
 nmake.exe /nologo /f makefiles\Windows.mak build