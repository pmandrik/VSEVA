
import ROOT
from array import array
import copy
from hadd import *

def get_CMS_EFT_benchmarks( name_, year_, CMS_fake = False):
  name, year = str(name_), str(year_)
  answer = None
  if name == "SM" :  answer = [1, 1, 0, 0, 0]
  if name == "box" : answer = [0, 1, 0, 0, 0]
  if name ==  "1" : answer = [7.5, 1, -1, 0, 0]
  if name ==  "2" : answer = [1.0, 1.0, 0.5, -0.8, 0.6]
  if name ==  "3" : answer = [1.0, 1.0, -1.5, 0.0, -0.8]
  if name ==  "4" : answer = [-3.5, 1.5, -3.0, 0.0, 0.0]
  if name ==  "5" : answer = [1.0, 1.0, 0.0, 0.8, -1.0]
  if name ==  "6" : answer = [2.4, 1.0, 0.0, 0.2, -0.2]
  if name ==  "7" : answer = [5.0, 1.0, 0.0, 0.2, -0.2]
  if name ==  "8" : answer = [15.0, 1.0, 0.0, -1.0, 1.0]
  if name ==  "9" : answer = [1.0, 1.0, 1.0, -0.6, 0.6]
  if name ==  "10" : answer = [10.0, 1.5, -1.0, 0.0, 0.0]
  if name ==  "11" : answer = [2.4, 1.0, 0.0, 1.0, -1.0]
  if name ==  "12" : answer = [15.0, 1.0, 1.0, 0.0, 0.0]

  if (year == "2017" or year == "2018") and answer and CMS_fake:
    answer[4] = 1.0
    answer[0], answer[1] = answer[1], answer[0]
  return answer

def get_A_values(input_name, bin_step):
  A_values_map = []
  with open( input_name ) as A_values_f:
    content = A_values_f.read()
    for line in content.split("\n"):
      data = line.split(",")
      if len(data) < 2 : continue
      mass = float( data[0] )
      A_values = [ float(A) for A in data[1:] ]
      A_values_map += [ [mass+bin_step/2, A_values] ]
  return A_values_map

def get_A_values_Carvalho(input_name):
  A_values_map = []
  sum = 0
  sum_events = 0
  with open( input_name ) as A_values_f:
    content = A_values_f.read()
    for line in content.split("\n"):
      data = line.split(" ")
      if len(data) < 2 : continue
      mass   = float( data[1] )
      ctheta = float( data[2] )
      nevents = float( data[3] ) # / (3000000.)
      A_values = [ float(A) for A in data[5:] ]
      A_values_map += [ [mass, ctheta, nevents/3000000, A_values] ]
      #print mass, ctheta, A_values
      sum += nevents * A_values[0]
      sum_events += nevents
  #print sum_events, sum
  return A_values_map

class ReweightCarvalho():
  # https://arxiv.org/pdf/1710.08261.pdf based
  def __init__(self, input_lo='coefficientsByBin_extended_3M_costHHSim_59-4.txt'):
    self.mhh_bins = [   250.,    260.,    270.,    280.,    290.,    300.,    310.,
	          320.,    330.,    340.,    350.,    360.,    370.,    380.,
	          390.,    400.,    410.,    420.,    430.,    440.,    450.,
	          460.,    470.,    480.,    490.,    500.,    510.,    520.,
	          530.,    540.,    550.,    560.,    570.,    580.,    590.,
	          600.,    610.,    620.,    630.,    640.,    650.,    660.,
	          670.,    680.,    690.,    700.,    750.,    800.,    850.,
	          900.,    950.,   1000.,   1100.,   1200.,   1300.,   1400.,
	         1500.,   1750.,   2000.,  50000.]
    self.cos_theta = [ 0.,  0.40000001,  0.60000002,  0.80000001,  1. ]
    self.A_map = get_A_values_Carvalho( input_lo )

  def GetEFTBenchmark(self, name, year):
    couplings = get_CMS_EFT_benchmarks( name, year)
    return couplings

  # https://phab.hepforge.org/source/rosettagit/browse/master/Rosetta/interfaces/dihiggs/AnalyticalReweighter.py
  def analytical_formula(self, kl, kt, c2, cg, c2g, A):
    return A[0]*kt**4 + A[1]*c2**2 + (A[2]*kt**2 + A[3]*cg**2)*kl**2 \
           + A[4]*c2g**2 + ( A[5]*c2 + A[6]*kt*kl )*kt**2  + (A[7]*kt*kl \
	         + A[8]*cg*kl )*c2 + A[9]*c2*c2g  + (A[10]*cg*kl \
	         + A[11]*c2g)*kt**2+ (A[12]*kl*cg + A[13]*c2g )*kt*kl \
	         + A[14]*cg*c2g*kl

  def GetDiffXsection(self, m_hh, cos_theta, eft_parameters):
    kl, kt, c2, cg, c2g = eft_parameters
    if m_hh < 250 or cos_theta < 0: 
      # print "ReweightCarvalho.GetDiffXsection(): Warning, m_hh =", m_hh, "cos_theta =", cos_theta
      return 0

    sm_xsection = 16.60711696
    for m_index, val_m in enumerate(self.mhh_bins[1:]):
      if m_hh > val_m : continue
      for c_index, val_c in enumerate(self.cos_theta[1:]):
        if cos_theta > val_c : continue
        A_values_ = self.A_map[ (len(self.cos_theta)-1) * m_index + c_index ]

        dm   = val_m - self.mhh_bins[m_index]
        dcos = val_c - self.cos_theta[c_index]
        # print "!!!", m_hh, cos_theta, val_c, val_m, A_values_[0], A_values_[1]
        A_values = A_values_[3]
        # print "A",A_values[0:5]
        # print self.analytical_formula(kl, kt, c2, cg, c2g, A_values)
        # print dm, dcos
        return self.analytical_formula(kl, kt, c2, cg, c2g, A_values) * A_values_[2] * sm_xsection / dm / dcos
        
    # print "ReweightCarvalho.GetDiffXsection(): Warning, m_hh =", m_hh, "cos_theta =", cos_theta, "out of range"
    return 0

  def GetXsection(self, eft_parameters):
    kl, kt, c2, cg, c2g = eft_parameters
    A_values = [2.09078, 10.1517, 0.282307, 0.101205, 1.33191, -8.51168, -1.37309, 2.82636, 1.45767, -4.91761, -0.675197, 1.86189, 0.321422, -0.836276, -0.568156]
    sm_xsection = 16.60711696
    return sm_xsection * self.analytical_formula(kl, kt, c2, cg, c2g, A_values)

class ReweightGudrin():
  # https://arxiv.org/abs/1806.05162 based
  def __init__(self, input_lo='LO-Ais-13TeV.csv', input_nlo='NLO-Ais-13TeV.csv', bin_step=20):

    self.bin_step = bin_step
    self.A_values_map_LO  = get_A_values( input_lo, bin_step )
    self.A_values_map_NLO = get_A_values( input_nlo, bin_step )

  def CouplingsToEWChL(self, k_lambda, k_t, c2, cg, c2g):
    ct  = k_t
    ctt = c2
    c3  = k_lambda
    cg  = cg * 2. / 3.
    cgg = c2g * (-1.) / 3.
    return c3, ct, ctt, cg, cgg

  def GetEFTBenchmark(self, name, year):
    couplings = get_CMS_EFT_benchmarks( name, year)
    return self.CouplingsToEWChL(couplings[0], couplings[1], couplings[2], couplings[3], couplings[4]);

  def GetDiffXsection(self, m_hh, eft_parameters, order="nlo"):
    c3, ct, ctt, cg, cgg = eft_parameters
    if m_hh < 250 : 
      # print "ReweightGudrin.GetDiffXsection(): Warning, m_hh =", m_hh, "< 250"
      return 0

    # print c3, ct, ctt, cg, cgg
    couplings = [ pow(ct,4), pow(ctt,2), pow(c3 * ct,2), pow(c3*cg,2), pow(cgg,2), ctt*pow(ct,2), pow(ct,3)*c3,
                  ct*c3*ctt, cg*c3*ctt, ctt*cgg, pow(ct,2)*cg*c3, pow(ct,2)*cgg, 
                  ct*pow(c3,2)*cg, ct*c3*cgg, cg*c3*cgg, 
                  pow(ct,3)*cg, ct*ctt*cg, ct*c3*pow(cg,2), cg*ct*cgg, 
                  pow(ct*cg,2), ctt*pow(cg,2), pow(cg,3)*c3, pow(cg,2)*cgg ]
    
    A_map = self.A_values_map_NLO
    if order=="lo":
      couplings = couplings[:15]
      A_map = self.A_values_map_LO

    for item in A_map:
      mass = item[0]
      if m_hh > mass : continue
      weight = 0
      for A, kappa in zip(item[1], couplings):
        # print A, kappa, A * kappa
        weight += A * kappa
      return weight
    # print "ReweightGudrin.GetDiffXsection(): Warning, m_hh =", m_hh, " out of mass range"
    return 0;

  def GetXsection2(self, eft_parameters, order="nlo"):
    xsection = 0
    for mass in xrange(255, 1000, self.bin_step):
      xsection += self.GetDiffXsection(mass, eft_parameters, order) * self.bin_step
    return xsection
    
  def GetXsection(self, eft_parameters, order="nlo"):
    c3, ct, ctt, cg, cgg = eft_parameters
    A_values_lo  = [2.08059, 10.2011, 0.27814, 0.314043, 12.2731, -8.49307, -1.35873, 2.80251, 2.48018, 14.6908, -1.15916, -5.51183, 0.560503, 2.47982, 2.89431]
    A_values_nlo = [2.23389, 12.4598, 0.342248, 0.346822, 13.0087, -9.6455, -1.57553, 3.43849, 2.86694, 16.6912, -1.25293, -5.81216, 0.649714, 2.85933, 3.14475, 
                    -0.00816241, 0.0208652, 0.0168157, 0.0298576, -0.0270253, 0.0726921, 0.0145232, 0.123291]
    couplings = [ pow(ct,4), pow(ctt,2), pow(c3 * ct,2), pow(c3*cg,2), pow(cgg,2), ctt*pow(ct,2), pow(ct,3)*c3,
                  ct*c3*ctt, cg*c3*ctt, ctt*cgg, pow(ct,2)*cg*c3, pow(ct,2)*cgg, 
                  ct*pow(c3,2)*cg, ct*c3*cgg, cg*c3*cgg, 
                  pow(ct,3)*cg, ct*ctt*cg, ct*c3*pow(cg,2), cg*ct*cgg, 
                  pow(ct*cg,2), ctt*pow(cg,2), pow(cg,3)*c3, pow(cg,2)*cgg ]

    A_values = A_values_lo
    if order == "nlo" : A_values = A_values_nlo

    sm_xsection = 16.60711696
    if order == "nlo" : sm_xsection = 32.95
 
    xsection = 0
    for A, coupling in zip(A_values, couplings):
      xsection += A * coupling
    return xsection * sm_xsection

def make_prediction_hist(r, r_old, benchmark_title):
  
  benchmark_title = str(benchmark_title)
  benchmark   = r.GetEFTBenchmark( benchmark_title, 2016 )

  start_x = 250
  end_x   = 1030
  nbins   = (end_x-start_x+20)/20
  h0 = ROOT.TH1D("0", "EFT"+benchmark_title +" LO I", nbins, 240, 1040);
  h1 = ROOT.TH1D("1", "EFT"+benchmark_title +" LO II", nbins, 240, 1040);
  h2 = ROOT.TH1D("2", "EFT"+benchmark_title +" NLO II", nbins, 240, 1040);
    
  sum_lo = 0
  sum_nlo = 0
  for i in xrange(nbins):
    weight  = r.GetDiffXsection( start_x + 20 * i, benchmark, "lo" );
    h1.Fill( start_x + 20 * i, weight );
    sum_lo += weight * 20
    weight  = r.GetDiffXsection( start_x + 20 * i, benchmark, "nlo" );
    h2.Fill( start_x + 20 * i, weight );
    sum_nlo += weight * 20

  benchmark   = r_old.GetEFTBenchmark( benchmark_title, 2016 )
  sum_lo_old = 0
  if True :
    h0 = ROOT.TGraphErrors( len(r_old.mhh_bins)-2 );
    for j in xrange( len(r_old.mhh_bins)-1 ) : 
      weight = 0;
      mhh = (r_old.mhh_bins[j] + r_old.mhh_bins[j+1])/2
      dm = r_old.mhh_bins[j+1] - r_old.mhh_bins[j]
      for i in xrange(len(r_old.cos_theta)-1) :
        cos = (r_old.cos_theta[i+1] + r_old.cos_theta[i])/2
        dcos = r_old.cos_theta[i+1] - r_old.cos_theta[i]
        weight += r_old.GetDiffXsection(mhh, cos, benchmark ) * dcos;
      # print j, mhh, weight, dm/2
      sum_lo_old += weight * dm
      h0.SetPoint(j, mhh, weight)
      h0.SetPointError(j, dm/2, 0)

  print "xsections ... ", sum_lo, sum_lo_old # 16.60711696 19.8488317355

  canv = ROOT.TCanvas("canv", "canv", 640, 480)
  h1.SetLineColor(2)
  h2.SetLineColor(3)
  h0.SetLineColor(4)
  
  title = benchmark_title
  h2.SetTitle("EFT benchmark "+title)

  if False:
    for i in xrange( h0.GetN() ) : h0.GetY()[i] /= sum_lo_old; 
    h1.Scale(1./sum_lo)  
    h2.Scale(1./sum_nlo)

  for h in [h1, h2, h0]:
    h.SetLineWidth(3)
    h.GetXaxis().SetTitle("M_{HH} [GeV]");
    h.GetYaxis().SetTitle("d#sigma/dm [fb/GeV]");
  h2.SetStats(False);

  h2.Draw("hist")
  h1.Draw("hist same")
  h0.Draw("p")
  h2.GetYaxis().SetRangeUser(0., max(h2.GetMaximum(), h1.GetMaximum())*1.5);

  x1=0.55
  y1=0.75
  x2=0.90 
  y2=0.88
  legend = ROOT.TLegend(x1,y1,x2,y2);
  #legend.SetLineColor(0);
  legend.SetLineWidth(3);
  #ROOT.gStyle.SetLegendBorderSize(3);
  legend.AddEntry(h0, "LO I", "lp");
  legend.AddEntry(h1, "LO II", "lp");
  legend.AddEntry(h2, "NLO II (normalised to LO)", "lp");
  h2.Scale( h1.Integral() / h2.Integral() );
  h2.GetYaxis().SetRangeUser(0., max(h2.GetMaximum(), h1.GetMaximum())*1.5);
  legend.Draw();

  canv.Print( "out/"+str(benchmark_title)+".png" );
  return h0;

def reweight_file(inp_file_names, inp_tree_names, inp_orders, inp_benchmarks_, inp_factors, out_path, out_file_name) :
    print "Reweight to", out_file_name
    r_gudrin   = ReweightGudrin()
    r_carvalho = ReweightCarvalho()

    input_files = " "
    import os

    index = 0
    for inp_file_name, inp_tree_name, inp_order, inp_benchmark_, factor in zip(inp_file_names, inp_tree_names, inp_orders, inp_benchmarks_, inp_factors):
      print "Process ... ", inp_file_name, inp_tree_name, inp_order, inp_benchmark_
      inp_benchmark   = r_gudrin.GetEFTBenchmark( inp_benchmark_, 2017 )
      inp_benchmark_old   = r_carvalho.GetEFTBenchmark( inp_benchmark_, 2017 )

      os.system('cp ' + inp_file_name + " " + out_path + "/tmp_" + str(index) + out_file_name )
      inp_file_name = out_path + "/tmp_" + str(index) + out_file_name
      input_files += " " + inp_file_name + " "
      index += 1

      inp_file = ROOT.TFile( inp_file_name, "UPDATE")
      inp_tree = inp_file.Get( inp_tree_name )

      out_benchmark, out_benchmark_old = [], []
      weight_lo, weight_lo_carv, weight_nlo = [], [], []
      br_weight_lo, br_weight_lo_carv, br_weight_nlo = [], [], []
      for i, mark in enumerate( ["SM", "box", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11] ): 
        out_benchmark       += [ r_gudrin.GetEFTBenchmark( mark, 2017 )   ]
        out_benchmark_old   += [ r_carvalho.GetEFTBenchmark( mark, 2017 ) ]

        weight_lo       += [ array( 'd', [ 0 ] ) ]
        weight_lo_carv  += [ array( 'd', [ 0 ] ) ]
        weight_nlo      += [ array( 'd', [ 0 ] ) ]
        br_weight_lo       += [ inp_tree.Branch('weight_lo_' + str(mark),  weight_lo[i],  'weight_lo_' + str(mark) + '/D') ]
        br_weight_lo_carv  += [ inp_tree.Branch('weight_lo_carv_' + str(mark),  weight_lo_carv[i],  'weight_lo_carv_' + str(mark) + '/D') ]
        br_weight_nlo      += [ inp_tree.Branch('weight_nlo_' + str(mark), weight_nlo[i], 'weight_nlo_' + str(mark) + '/D') ]

      #inp_tree.SetBranchStatus("*", 0);
      #inp_tree.SetBranchStatus("gen_HHi_tlv", 1);
      #inp_tree.SetBranchStatus("gen_Hi_yy_tlv", 1);
      for event_i, entry in enumerate(inp_tree):   
        m_HH = entry.gen_HHi_tlv.M()
        cos_theta = abs( entry.gen_Hi_yy_tlv.CosTheta() )

        dx_inp = r_gudrin.GetDiffXsection( m_HH, inp_benchmark, inp_order );
        dx_inp_carv  = r_carvalho.GetDiffXsection( m_HH, cos_theta, inp_benchmark_old);

        inp_tree.GetEntry( event_i )
        for i, mark in enumerate( ["SM", "box", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11] ): 
          dx_lo  = r_gudrin.GetDiffXsection( m_HH, out_benchmark[i], "lo" );
          dx_nlo = r_gudrin.GetDiffXsection( m_HH, out_benchmark[i] );
          dx_lo_carv   = r_carvalho.GetDiffXsection( m_HH, cos_theta, out_benchmark_old[i]);

          if dx_inp < 0.00000001 :
            weight_lo[i][0]  = 0
            weight_lo_carv[i][0] = 0
            weight_nlo[i][0] = 0
          else :
            weight_lo[i][0]  = factor * dx_lo  / dx_inp
            weight_lo_carv[i][0] = factor * dx_lo_carv / dx_inp_carv;
            weight_nlo[i][0] = factor * dx_nlo  / dx_inp

          # print mark, out_benchmark[i], weight_nlo[i][0]

          br_weight_lo[i].Fill()
          br_weight_nlo[i].Fill()
          br_weight_lo_carv[i].Fill()

      print inp_tree.GetEntries()
      inp_tree.Write()
      inp_file.Close()

    import os
    print 'hadd -f ' + out_path + out_file_name + input_files
    os.system('hadd -f ' + out_path + out_file_name + input_files)

    print "done! ... "

if __name__ == "__main__" :
  import sys

  
  r1   = ReweightGudrin()
  r2 = ReweightCarvalho()
  for bm in ["SM", 1, 2, 3 ,4 ,5 ,6 ,7 ,8 ,9 ,10 ,11 ,12] :
    make_prediction_hist(r1, r2, bm)
  

  # r_gudrin   = ReweightGudrin();
  # print r_gudrin.GetDiffXsection(999, r_gudrin.GetEFTBenchmark("7", "2017"), "nlo" );

  if False :

    inp_path="/afs/cern.ch/work/p/pmandrik/dihiggs/8_mvanaluse/VSEVA/HHWWgg/output/chanels_sys_2017/"
    out_path="/afs/cern.ch/work/p/pmandrik/dihiggs/8_mvanaluse/VSEVA/HHWWgg/output/reweighted_2017/"

    for systematic in ["Def", "FNUFEBDown", "FNUFEBUp", "FNUFEEDown", "FNUFEEUp", "MCScaleGain1EBDown", "MCScaleGain1EBUp", "MCScaleGain6EBDown", "MCScaleGain6EBUp", "MCScaleHighR9EBDown", "MCScaleHighR9EBUp", "MCScaleHighR9EEDown", "MCScaleHighR9EEUp", "MCScaleLowR9EBDown", "MCScaleLowR9EBUp", "MCScaleLowR9EEDown", "MCScaleLowR9EEUp", "MCSmearHighR9EBPhiDown", "MCSmearHighR9EBPhiUp", "MCSmearHighR9EBRhoDown", "MCSmearHighR9EBRhoUp", "MCSmearHighR9EEPhiDown", "MCSmearHighR9EEPhiUp", "MCSmearHighR9EERhoDown", "MCSmearHighR9EERhoUp", "MCSmearLowR9EBPhiDown", "MCSmearLowR9EBPhiUp", "MCSmearLowR9EBRhoDown", "MCSmearLowR9EBRhoUp", "MCSmearLowR9EEPhiDown", "MCSmearLowR9EEPhiUp", "MCSmearLowR9EERhoDown", "MCSmearLowR9EERhoUp", "MaterialCentralBarrelDown", "MaterialCentralBarrelUp", "MaterialForwardDown", "MaterialForwardUp", "MaterialOuterBarrelDown", "MaterialOuterBarrelUp", "MvaShiftDown", "MvaShiftUp", "ShowerShapeHighR9EBDown", "ShowerShapeHighR9EBUp", "ShowerShapeHighR9EEDown", "ShowerShapeHighR9EEUp", "ShowerShapeLowR9EBDown", "ShowerShapeLowR9EBUp", "ShowerShapeLowR9EEDown", "ShowerShapeLowR9EEUp", "SigmaEOverEShiftDown", "SigmaEOverEShiftUp","JEC_AbsoluteUp", "JEC_AbsoluteDown", "JEC_Absolute_2017Up", "JEC_Absolute_2017Down", "JEC_BBEC1Up", "JEC_BBEC1Down", "JEC_BBEC1_2017Up", "JEC_BBEC1_2017Down", "JEC_EC2Up", "JEC_EC2Down", "JEC_EC2_2017Up", "JEC_EC2_2017Down", "JEC_FlavorQCDUp", "JEC_FlavorQCDDown", "JEC_HFUp", "JEC_HFDown", "JEC_HF_2017Up", "JEC_HF_2017Down", "JEC_RelativeBalUp", "JEC_RelativeBalDown", "JEC_RelativeSample_2017Up", "JEC_RelativeSample_2017Down", "UnclusteredMETUp", "UnclusteredMETDown"]:


    # for systematic in ["Def"] : 

        fname = "hzura_2017_EFT_all_v1_" + systematic + "_Events_ch78.root"

        inp_files  = []
        benchmarks = []
        factors    = []
        def add_node(file, bench, fact):
          global inp_files
          global benchmarks
          global factors
          inp_files  += [ file ]
          benchmarks += [ bench ]
          factors    += [ fact ]

        add_node(inp_path + "hzura_2017_SM_fsim_v0_" + systematic + "_Events_ch78.root", "SM", 399773/1000000.)
        add_node(inp_path + "hzura_2017_1_fsim_v0_"  + systematic + "_Events_ch78.root", 0 ,   387757/1000000.)
        add_node(inp_path + "hzura_2017_2_fsim_v0_"  + systematic + "_Events_ch78.root", 1 ,   399742/1000000.)
        add_node(inp_path + "hzura_2017_3_fsim_v0_"  + systematic + "_Events_ch78.root", 2 ,   399780/1000000.)
        add_node(inp_path + "hzura_2017_4_fsim_v0_"  + systematic + "_Events_ch78.root", 3 ,   399752/1000000.)
        add_node(inp_path + "hzura_2017_5_fsim_v0_"  + systematic + "_Events_ch78.root", 4 ,   365791/1000000.)
        add_node(inp_path + "hzura_2017_6_fsim_v0_"  + systematic + "_Events_ch78.root", 5 ,   373777/1000000.)
        add_node(inp_path + "hzura_2017_7_fsim_v0_"  + systematic + "_Events_ch78.root", 6 ,   377789/1000000.)
        add_node(inp_path + "hzura_2017_9_fsim_v0_"  + systematic + "_Events_ch78.root", 8 ,   399735/1000000.)
        add_node(inp_path + "hzura_2017_10_fsim_v0_"  + systematic + "_Events_ch78.root", 9 , 365788/1000000.)
        add_node(inp_path + "hzura_2017_11_fsim_v0_"  + systematic + "_Events_ch78.root", 10 , 399751/1000000.)
        add_node(inp_path + "hzura_2017_12_fsim_v0_"  + systematic + "_Events_ch78.root", 11 , 399752/1000000.)

        orders, tree_names = [], []
        for file in inp_files:
          orders += ["lo"]
          tree_names += ["data"]

        reweight_file(inp_files, tree_names, orders, benchmarks, factors, out_path, fname)





