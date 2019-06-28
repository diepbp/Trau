#!bin/bash
apt-get update && apt-get install -y g++ cmake uuid-dev && rm -rf /var/lib/apt/lists/*

wget -O openfst.tar.gz "http://www.openfst.org/twiki/pub/FST/FstDownload/openfst-1.6.8.tar.gz" 
wget -O antlr4.zip "http://www.antlr.org/download/antlr4-cpp-runtime-4.7.2-source.zip"
wget -O z3.tar.gz "https://github.com/Z3Prover/z3/archive/z3-4.8.4.tar.gz"
wget -O trau.tar.gz "https://github.com/diepbp/Trau/archive/v1.3.1.tar.gz"
dir=$PWD
echo "Install FST"
cd $dir && rm -rf /usr/src/openfst && mkdir -p /usr/src/openfst && tar -xzC /usr/src/openfst --strip-components=1 -f openfst.tar.gz && rm -rf openfst.tar.gz && cd /usr/src/openfst && ./configure --enable-far && make && make install && rm -rf /usr/src/openfst
# Install ANTLR4 C++ Runtime
echo "Install antlr4"
cd $dir && rm -rf /usr/src/antlr4 && mkdir -p /usr/src/antlr4 && unzip antlr4.zip -d /usr/src/antlr4 && rm -rf antlr4.zip && cd /usr/src/antlr4 && cmake . && make && make install && rm -rf /usr/src/antlr4

# Install Z3
echo "Install Z3"
cd $dir && rm -rf /usr/src/z3 && mkdir -p /usr/src/z3 && tar -xzC /usr/src/z3 --strip-components=1 -f z3.tar.gz && rm -rf z3.tar.gz && cd /usr/src/z3 && python scripts/mk_make.py && cd build && make && make install && rm -rf /usr/src/z3

# Install Trau 
echo "Install Trau +"
cd $dir && rm -rf /usr/share/workspace/trau && mkdir -p /usr/share/workspace/trau && tar -xzC /usr/share/workspace/trau --strip-components=1 -f trau.tar.gz && rm -rf trau.tar.gz
echo "Install custom-z3"
cd /usr/share/workspace/trau && unzip z3-z3-4.4.1.0.zip && mkdir -p /usr/share/workspace/custom-z3 && cp -r z3-z3-4.4.1.0 /usr/share/workspace/custom-z3 && cd /usr/share/workspace/custom-z3/z3-z3-4.4.1.0 && python scripts/mk_make.py --prefix=/usr/share/workspace/custom-z3 && cd build && sed -i -e 's/CXXFLAGS= /CXXFLAGS= -std=c++03 /' config.mk && make && make install && export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:'/usr/share/workspace/custom-z3/lib:/usr/local/lib' && cd /usr/share/workspace/trau/build && sed -i -e 's|/Users/diepbp/Documents/customZ3|/usr/share/workspace/custom-z3|' config.mk && make clean && make && mv Trau /usr/local/bin/trau && chmod 755 /usr/local/bin/trau
