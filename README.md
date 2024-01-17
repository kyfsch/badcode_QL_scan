https://stackoverflow.com/questions/55078713/extract-function-code-from-c-sourcecode-file-with-python

Static Analyzers NIST masterlist: https://www.nist.gov/itl/ssd/software-quality-group/source-code-security-analyzers
Sorting out the newer stuff from that list:
  CodeValor https://www.sentar.com/codevalor/ price: ?!
  CodeThreat https://www.codethreat.com/product/self-hosted free community version 
  Flawntr https://www.cybertest.com/secure-code-review price: ?!
  FlawFinder https://dwheeler.com/flawfinder/ FREE but maybe older
  	---> I was sketched out I couldn't find a latest version date, but apparently GitLab SAST actually uses
  		FlawFinder as its C/C++ engine
  Polyspace https://www.mathworks.com/products/polyspace-bug-finder.html has education license option
  LucentSky AVM https://www.lucentsky.com/en/avm
  Klocwork https://www.perforce.com/products/klocwork has free trial
  Helix QAC https://www.perforce.com/products/helix-qac [this one is cool because it's safety-critical specific]

  Conclusion on scanners:
  GitLab SAST uses FlawFinder and Semgrep for C/C++, both of which are free and seem trusted. Might be worth running both for a comparison?
  https://github.com/david-a-wheeler/flawfinder
  https://github.com/semgrep/semgrep
