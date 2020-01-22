import ROOT
ROOT.gROOT.SetBatch(True)
#ROOT.TColor.kRed
#ROOT.TColor.kBlue
import array
from ROOT import THistPainter, TH2,TCanvas, TColor
ROOT.gStyle.SetOptStat(0)
from os.path import basename


outdir = "./"
import os
try:
  os.makedirs(outdir)
except OSError:
  if not os.path.isdir(outdir): raise

# Creating an output file
outputfile = ROOT.TFile(outdir+"/btagging.root", "RECREATE")

#c2v20_file
#hists=[]
coupling=["1prong ttbar FF","3 prong ttbar FF"]
color=[ROOT.kGreen, ROOT.kRed]# ROOT.kYellow,ROOT.kBlack]
files=["/usatlas/u/psaha/usatlasdata/2018_analysis/source/FrameworkExe_HH_bbtautau/macros/1btag/FF_1prong_ttbar_23rdJuly_1btag.root",
       "/usatlas/u/psaha/usatlasdata/2018_analysis/source/FrameworkExe_HH_bbtautau/macros/1btag/FF_3prong_ttbar_23rdJuly_1btag.root"]
#histo_list=["h_hh_mass","h_mjj","h_deltaEta_jet","h_hh_pt", "h_higgs_pT","h_bquark_pT", "h_bb_pT","h_bb_mass","h_tau_pT","h_el_pT", "h_mu_pT","h_tautau_lh_mass","h_tautau_lh_vis_mass"]
#units= ["GeV","GeV","","GeV","GeV","GeV","GeV","GeV","GeV","GeV","GeV","GeV","GeV"]
#outputfile.cd()





#-----------------------------------------------------------------------------------------------------



T1= ROOT.TText()
T1.SetTextFont(42)
T1.SetTextAlign(21)
canvas_1= ROOT.TCanvas("canvas","canvas", 10,10,1000,1000)
stack_1 = ROOT.THStack("canvas_1", "")
box= ROOT.TLegend(0.7,0.7, 1.0, 0.9)     #(0.1,0.7,0.48,0.9)  #(0.7,0.7, 1.0, 0.9)
Tfile_list=[]
for i in xrange(2):
    filename= ROOT.TFile(files[i])
    Tfile_list.append(filename)

for i in xrange(2):
    
    
    hist_str= "fakes_ttbar"
    histo1= Tfile_list[i].Get(hist_str)
    col= color[i]
    print col
    histo1.SetLineColor(col)
    histo1.SetLineWidth(3)
    histo1.GetXaxis().SetTitle("TauPt")
    histo1.GetYaxis().SetTitle(" ttbar Fake Factor")
    print type(histo1)
    #hists.append(histo1)
    print histo1
    stack_1.Add(histo1)
    box.AddEntry(histo1, "" + coupling[i], "f")
    print i	   


#canvas_1.cd()


stack_1.Draw("nostack")
stack_1.GetXaxis().SetTitle("Tau Pt (GeV)");
stack_1.GetYaxis().SetLabelOffset(0.01);
stack_1.GetYaxis().SetTitleFont(43);
stack_1.GetYaxis().SetTitleSize(20);

#stack_1.GetYaxis().SetLabeOffset(-0.1);

stack_1.GetYaxis().SetTitle("ttbar Fake Factor");
        
T1.DrawTextNDC(.5,.95,"{}".format("ttbar FF Vs tauPt in 1b-tag"))
box.SetHeader(" ttbar Fake Factor 1btag")
box.SetTextSize(0.02)
box.Draw()
canvas_1.Print(outdir+"/FFttbar_1btag.pdf")


outputfile.Write()
outputfile.Close()
