

def get_jets( collection_name, size ):
  answer_floats = []
  answer_tlvs   = []

  col_parts = ["N"]
  tlv_parts = ["e", "pt", "eta", "phi", "m"]
  jet_parts = ["tau1", "tau2", "tau3", "subjetsSoftDrop_size"]
  jet_tlv_parts = ["softDroppedJet", "leadingSoftDroppedSubJet", "trailingSoftDroppedSubJet"]

  for part in col_parts:
    answer_floats += [ collection_name + "_" + part ]
  
  for i in xrange(size):
    name = collection_name + "_" + str(i)
    answer_tlvs += [ name ]
    for part in tlv_parts + jet_parts:
      answer_floats += [ name + "_" + part ]
    
    for part in jet_tlv_parts:
      answer_tlvs += [ name + "_" + part ]
      for subpart in tlv_parts:
        answer_floats += [ name + "_" + part + "_" + subpart ]

  return answer_floats, answer_tlvs

def set_analyse_hists(plotter):

  plotter.add_TH1("test_a", 0, 400 )
  plotter.add_TH2("test_b", 0, 2, 0, 400)

vars_to_save = [ "weight",
                 "H_m", "H_pt", "H_eta", "dPhi_H_lj", "dR_H_lj", "dPhi_H_lbj", "dR_H_lbj",
                 "lj_pt", "lj_eta", 
                 "lbj_pt", "lbj_eta",
                 "dPhi_photons", "dR_photons", "ED_photons",
                 "photon_1v_eta", "photon_2v_eta",
                 "photon_1v_pt", "photon_2v_pt",
                 "N_jets", "N_bjets", 
                 "weight_sel_1",
                 "weight_sel_2",
                 "weight_sel_3",
]

#
# 
#
#
#
#

part_vars = ["tau1", "tau2", "tau3"]














