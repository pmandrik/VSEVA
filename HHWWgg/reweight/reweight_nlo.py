
import ROOT
from array import array
import copy

def get_CMS_EFT_benchmarks( name_, year_ ):
  name, year = str(name_), str(year_)
  answer = None
  if name == "SM" :  answer = [1, 1, 0, 0, 0]
  if name == "box" : answer = [0, 1, 0, 0, 0]
  if name ==  "0" : answer = [7.5, 1, -1, 0, 0]
  if name ==  "1" : answer = [1.0, 1.0, 0.5, -0.8, 0.6]
  if name ==  "2" : answer = [1.0, 1.0, -1.5, 0.0, -0.8]
  if name ==  "3" : answer = [-3.5, 1.5, -3.0, 0.0, 0.0]
  if name ==  "4" : answer = [1.0, 1.0, 0.0, 0.8, -1.0]
  if name ==  "5" : answer = [2.4, 1.0, 0.0, 0.2, -0.2]
  if name ==  "6" : answer = [5.0, 1.0, 0.0, 0.2, -0.2]
  if name ==  "7" : answer = [15.0, 1.0, 0.0, -1.0, 1.0]
  if name ==  "8" : answer = [1.0, 1.0, 1.0, -0.6, 0.6]
  if name ==  "9" : answer = [10.0, 1.5, -1.0, 0.0, 0.0]
  if name ==  "10" : answer = [2.4, 1.0, 0.0, 1.0, -1.0]
  if name ==  "11" : answer = [15.0, 1.0, 1.0, 0.0, 0.0]

  if year_ == 2017 and answer:
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
      print "ReweightCarvalho.GetDiffXsection(): Warning, m_hh =", m_hh, "cos_theta =", cos_theta
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
        
    print "ReweightCarvalho.GetDiffXsection(): Warning, m_hh =", m_hh, "cos_theta =", cos_theta, "out of range"
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
      print "ReweightGudrin.GetDiffXsection(): Warning, m_hh =", m_hh, "< 250"
      return 0

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
        weight += A * kappa
      return weight
    print "ReweightGudrin.GetDiffXsection(): Warning, m_hh =", m_hh, " out of mass range"
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
  benchmark   = r.GetEFTBenchmark( benchmark_title, 2017 )

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

  benchmark   = r_old.GetEFTBenchmark( benchmark_title, 2017 )
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
      print j, mhh, weight, dm/2
      sum_lo_old += weight * dm
      h0.SetPoint(j, mhh, weight)
      h0.SetPointError(j, dm/2, 0)

  print "xsections ... ", sum_lo, sum_lo_old # 16.60711696 19.8488317355

  canv = ROOT.TCanvas("canv", "canv", 640, 480)
  h1.SetLineColor(2)
  h2.SetLineColor(3)
  h0.SetLineColor(4)
  h2.SetTitle("EFT"+benchmark_title)

  if False:
    for i in xrange( h0.GetN() ) : h0.GetY()[i] /= sum_lo_old; 
    h1.Scale(1./sum_lo)  
    h2.Scale(1./sum_nlo)

  for h in [h1, h2, h0]:
    h.SetLineWidth(3)
    h.GetXaxis().SetTitle("M_{HH}");
    h.GetYaxis().SetTitle("d#sigma/dm / #sigma");
  h2.SetStats(False);

  h2.Draw("hist")
  h1.Draw("hist same")
  h0.Draw("P")
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
  legend.AddEntry(h2, "NLO II", "lp");
  legend.Draw();

  canv.Print( "out/"+str(benchmark_title)+".png" );
  return h0;

def reweight_file(r_gudrin, r_carvalho, inp_file_name, inp_tree_name, inp_order, inp_benchmark_, out_file_name, out_benchmark_) :
    inp_benchmark   = r_gudrin.GetEFTBenchmark( inp_benchmark_, 2017 )
    out_benchmark   = r_gudrin.GetEFTBenchmark( out_benchmark_, 2017 )

    inp_benchmark_old   = r_carvalho.GetEFTBenchmark( inp_benchmark_, 2017 )
    out_benchmark_old   = r_carvalho.GetEFTBenchmark( out_benchmark_, 2017 )

    inp_file = ROOT.TFile( inp_file_name, "read")
    inp_tree = inp_file.Get( inp_tree_name )

    out_file = ROOT.TFile( out_file_name, "RECREATE")
    out_tree = inp_tree.CopyTree("")

    weight_lo  = array( 'd', [ 0 ] )
    weight_lo_carv  = array( 'd', [ 0 ] )
    weight_nlo = array( 'd', [ 0 ] )
    br_weight_lo  = out_tree.Branch('weight_lo',  weight_lo,  'weight_lo/D')
    br_weight_lo_carv  = out_tree.Branch('weight_lo_carv',  weight_lo_carv,  'weight_lo_carv/D')
    br_weight_nlo = out_tree.Branch('weight_nlo', weight_nlo, 'weight_nlo/D')

    h0 = ROOT.TH1D("h0", "Reweight alt LO", (1050-250)/20, 250, 1050);

    for i, entry in enumerate(inp_tree):   
      m_HH = entry.gen_HHi_tlv.M()
      cos_theta = abs( entry.gen_Hi_yy_tlv.CosTheta() )

      dx_inp = r_gudrin.GetDiffXsection( m_HH, inp_benchmark, inp_order );
      dx_lo  = r_gudrin.GetDiffXsection( m_HH, out_benchmark, "lo" );
      dx_nlo = r_gudrin.GetDiffXsection( m_HH, out_benchmark );

      dx_inp_carv  = r_carvalho.GetDiffXsection( m_HH, cos_theta, inp_benchmark_old);
      dx_lo_carv   = r_carvalho.GetDiffXsection( m_HH, cos_theta, out_benchmark_old);

      out_tree.GetEntry( i )
      if dx_inp < 0.00000001 :
        weight_lo[0]  = 0
        weight_lo_carv[0] = 0
        weight_nlo[0] = 0
        br_weight_lo.Fill()
        br_weight_nlo.Fill()
        br_weight_lo_carv.Fill()
      else :
        h0.Fill( m_HH, dx_nlo  / dx_inp );
        weight_lo[0]  = dx_lo  / dx_inp
        weight_lo_carv[0] = dx_lo_carv / dx_inp_carv;
        weight_nlo[0] = dx_nlo  / dx_inp
        br_weight_lo.Fill()
        br_weight_nlo.Fill()
        br_weight_lo_carv.Fill()
        #print i, dx_lo_carv / dx_inp_carv

    #for i, e1 in enumerate(out_tree):
    #  print i, e1.weight_lo_carv

    canv = ROOT.TCanvas("canv", "canv", 640, 480)
    h0.Draw()
    canv.Print( str(out_benchmark_)+"_lo_gudrin_alt.png" );

    out_tree.Write()
    out_file.Close()

if __name__ == "__main__" :
  r = ReweightGudrin()
  r_old = ReweightCarvalho()

  if True :

    inp_path="/afs/cern.ch/work/p/pmandrik/dihiggs/8_mvanaluse/VSEVA/HHWWgg/output/chanels_sys/"
    out_path="/afs/cern.ch/work/p/pmandrik/dihiggs/8_mvanaluse/VSEVA/HHWWgg/output/reweighted/"

    for mark in ["SM", "box", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11] :
      #make_prediction_hist(r, r_old, mark)
      #break
      #print r.GetEFTBenchmark(mark), r_old.GetEFTBenchmark(mark)
      a= r.GetXsection(r.GetEFTBenchmark(mark, 2017), "lo")
      b= r.GetXsection2(r.GetEFTBenchmark(mark, 2017), "lo")
      # print r.GetEFTBenchmark(mark)
      # print r.GetEFTBenchmark(mark)[4], a/b
      # print r.GetXsection(r.GetEFTBenchmark(mark), "lo"), r_old.GetXsection(r_old.GetEFTBenchmark(mark))
      # continue
      # make_prediction_hist(r, mark, "lo")
      mark = str(mark)
      fname = "hzura_2017_" + mark + "_v7_Def_Events_ch78.root"
      if mark not in ["SM", "box"] :
        fname = "hzura_2017_EFT" + mark + "_v7_Def_Events_ch78.root"
      reweight_file(r, r_old, inp_path + "hzura_2017_SM_v7_Def_Events_ch78.root", "data", "lo", "SM", out_path + fname, mark)
      #break






