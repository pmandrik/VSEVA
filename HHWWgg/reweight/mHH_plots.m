NLOCoeffs = Import["NLO-Ais-14TeV.csv", "Data"];

nbins=Length[NLOCoeffs];
ncoeffs=23;

mhh = Table[NLOCoeffs[[j]][[1]], {j, 1, nbins}];
Do[
   A[i] = Table[NLOCoeffs[[j]][[i+1]], {j, 1, nbins}];
,{i,ncoeffs}];

Do[
sigma[ct_, c3_, ctt_, cg_, cgg_, bin_]:= 
   A[1][[bin]]*ct^4 + A[2][[bin]]*ctt^2 + A[3][[bin]]*c3^2*ct^2 + A[4][[bin]]*c3^2*cg^2 + A[5][[bin]]*cgg^2 + 
   A[6][[bin]]*ctt*ct^2 + A[7][[bin]]*ct^3*c3 + A[8][[bin]]*ct*c3*ctt + A[9][[bin]]*cg*c3*ctt + 
   A[10][[bin]]*ctt*cgg + A[11][[bin]]*ct^2*cg*c3 + A[12][[bin]]*ct^2*cgg + A[13][[bin]]*ct*c3^2*cg + 
   A[14][[bin]]*ct*c3*cgg + A[15][[bin]]*cg*c3*cgg + A[16][[bin]]*ct^3*cg + A[17][[bin]]*ct*ctt*cg + 
   A[18][[bin]]*ct*c3*cg^2 + A[19][[bin]]*cg*ct*cgg + A[20][[bin]]*ct^2*cg^2 + A[21][[bin]]*ctt*cg^2 + 
   A[22][[bin]]*cg^3*c3 + A[23][[bin]]*cg^2*cgg;
,{bin,1,nbins}]    
   
DiscretePlot[sigma[1, 1, 0, 0, 0, bin], {bin,1,40},ExtentSize->Full]  

(* Do[Print[sigma[1, 1, 0, 0, 0, bin]], {bin,1,40}] *)
