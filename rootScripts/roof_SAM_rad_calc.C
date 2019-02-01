using namespace std;
#include <iostream>

void roof_SAM_rad_calc(string modifier = "thickness",string units = "mm",int number = 6){
////to use, either run the parser_hallrad_root.sh with the modifier passed in, or use the 'SAMs' modifier with "benchmark" and any number/no number as the third entry



//For each file in the directory (list?) 
//  open the file and find the bin where the energy min for the cut is
//    for det 1006 (roof) counts of E>30MeV (25.12 is bin 75 on log X scale histograms) neutrons (maxes out at bin 94)
//    for det 1001 (LHRS) NEIL (Gold standard) (all three species)
//    for det 3201 (o ring) power/energy deposited (all three species)
//    take integrals of the entire histograms and take the ratio wrt the benchmarks
//    benchmark = noSAMs (with dump, without dump, with shielding, without shielding - with U, no SAMs is the official benchmark)
//    Make a new line entry in a overall output text file (.csv)
//  Plot the line graphs for the benchmark, mitigated, and worst case scenario summaries (just do it by hand for now)

//FIXME Read the modifier, number, and units from a parsed text file list, as in parserHallrad.sh (just use that as a loop to run this over an over again)
//  string modifier = "thickness";
//  int number = 6;
//  string units = "mm";
//use parserHallrad format to loop over files instead of doing it here
  TFile *file_in;
  string ben = "benchmark";
  int nEvents = 9e6;//9e6 for regular runs, 54e6 for benchmark runs;
  if (units!=ben){ //case = doing parameter space searches
    if (number==5 || number==6 || number==13) {
      nEvents=360e6;
    }
    else if (number>6 && number<13) {
      nEvents=90e6;
    }
    //file_in = TFile::Open(Form("output/list_%s_%i%s_hallRad.root",modifier.c_str(),number,units.c_str()));
    file_in = TFile::Open(Form("output/list_%s_%i%s_hallRad.root",modifier.c_str(),number,units.c_str()));
  }
  else{ //case = benchmark
    nEvents=450e6;
    file_in = TFile::Open(Form("output/list_%s_%s_hallRad.root",units.c_str(),modifier.c_str()));
  }
  
  //TH1D *hist_1001_g_neilLogX=(TH1D*)file_in->Get("Det_1001/ha_1001_g_neilLogX");
  //TH1D *hist_1001_e_neilLogX=(TH1D*)file_in->Get("Det_1001/ha_1001_e_neilLogX");
  //TH1D *hist_1001_n_neilLogX=(TH1D*)file_in->Get("Det_1001/ha_1001_n_neilLogX");
  TH1D *hist_1006_n_enerLogX=(TH1D*)file_in->Get("Det_1006/ha_1006_n_enerLogX");
  TH1D *hist_hSummary_enerLogX=(TH1D*)file_in->Get("hSummary_enerLogX");
  TH1D *hist_hSummary_neilLogX=(TH1D*)file_in->Get("hSummary_neilLogX");
  //TH1D *hist_3201_g_enerLogX=(TH1D*)file_in->Get("Det_3201/ha_3201_g_enerLogX");
  //TH1D *hist_3201_e_enerLogX=(TH1D*)file_in->Get("Det_3201/ha_3201_e_enerLogX");
  //TH1D *hist_3201_n_enerLogX=(TH1D*)file_in->Get("Det_3201/ha_i201_n_enerLogX");

  //NEIL_1001 = hist_1001_g_neilLogX->Integral(0,94) + hist_1001_e_neilLogX->Integral(0,94) + hist_1001_n_neilLogX->Integral(0,94);
  Double_t NEIL_1006 = hist_hSummary_neilLogX->GetBinContent(hist_hSummary_neilLogX->GetXaxis()->FindBin("1006 Avg"));
  Double_t NEIL_1006_error = hist_hSummary_neilLogX->GetBinError(hist_hSummary_neilLogX->GetXaxis()->FindBin("1006 Avg"));
  Double_t Flux_1006 = hist_1006_n_enerLogX->Integral(hist_1006_n_enerLogX->GetXaxis()->FindBin(25.12),94);
  Double_t Flux_1006_error = sqrt(Flux_1006/nEvents);//9M events is the number per run that the averages normalize to
  Double_t Energy_1006 = hist_hSummary_enerLogX->GetBinContent(hist_hSummary_enerLogX->GetXaxis()->FindBin("1006 Avg"));
  Double_t Energy_1006_error = hist_hSummary_enerLogX->GetBinError(hist_hSummary_enerLogX->GetXaxis()->FindBin("1006 Avg"));

  //Absolute per event: Neil in Roof 1006 = 0.00049331(9.51624e-07), Flux of neutrons to 1006, per million events (E>25.12 MeV) = 1.27963e-05(1.6863e-07), Energy in 1006 = 0.0934535(1.61385e-05)
  Double_t bench_NEIL_1006 = 4.9331e-4;
  Double_t bench_NEIL_1006_error = 9.51624e-07;  // error propagation = sigma = value after modification * relative error of subparts added in quadratures (sigma/previous value)
  Double_t bench_Flux_1006 = 1.27963e-05;
  Double_t bench_Flux_1006_error = 1.6863e-07 ;//54M is the number of beam events per run that the averages normalize to
  Double_t bench_Energy_1006 = 0.0934535;
  Double_t bench_Energy_1006_error = 1.61385e-06;

  Double_t NEIL_1006_ratio = NEIL_1006/bench_NEIL_1006;
  Double_t NEIL_1006_ratio_error = NEIL_1006_ratio*sqrt(pow(NEIL_1006_error/NEIL_1006,2)+pow(bench_NEIL_1006_error/bench_NEIL_1006,2));
  Double_t Flux_1006_ratio = Flux_1006/bench_Flux_1006;
  Double_t Flux_1006_ratio_error = Flux_1006_ratio*sqrt(pow(Flux_1006_error/Flux_1006,2)+pow(bench_Flux_1006_error/bench_Flux_1006,2));
  Double_t Energy_1006_ratio = Energy_1006/bench_Energy_1006;
  Double_t Energy_1006_ratio_error = Energy_1006_ratio*sqrt(pow(Energy_1006_error/Energy_1006,2)+pow(bench_Energy_1006_error/bench_Energy_1006,2));

//Energy numerically integrated in a loop
//for each bin Energy_3201+=the bin number times the bin contents
//for(int i=0; i<95; i++) {
//  Energy_3201 = Energy_3201 + hist_3201_g_enerLogX->GetBin(i)*hist_3201_g_enerLogX->GetBinContent(i) + hist_3201_e_enerLogX->GetBin(i)*hist_3201_e_enerLogX->GetBinContent(i) + hist_3201_n_enerLogX->GetBin(i)*hist_3201_n_enerLogX->GetBinContent(i);
//}

  ofstream file_out;
  ofstream NEIL_1006_out;
  ofstream Flux_1006_out;
  ofstream Energy_1006_out;
  file_out.open("output/SAM_analysis_overview.csv",std::ofstream::out | std::ofstream::app);
  NEIL_1006_out.open("output/SAM_analysis_NEIL_1006.csv",std::ofstream::out | std::ofstream::app);
  Flux_1006_out.open("output/SAM_analysis_Flux_1006.csv",std::ofstream::out | std::ofstream::app);
  Energy_1006_out.open("output/SAM_analysis_Energy_1006.csv",std::ofstream::out | std::ofstream::app);

  // This simulation analysis assumes a modifier describing a kind of benchmark wih 54 million events, or a varied parameter of units and number with 9 million events, and everything is normalized to NEIL, Flux, and Energy per 1M events on target
  if (units!=ben){ //case = doing parameter space searches
    file_out<<"Modified = "<<modifier<<", units = "<<units<<", number = "<<number<<std::endl;
    NEIL_1006_out<<modifier<<","<<units<<","<<number<<","<<NEIL_1006_ratio<<","<<NEIL_1006_ratio_error<<std::endl;
    Flux_1006_out<<modifier<<","<<units<<","<<number<<","<<Flux_1006_ratio<<","<<Flux_1006_ratio_error<<std::endl;
    Energy_1006_out<<modifier<<","<<units<<","<<number<<","<<Energy_1006_ratio<<","<<Energy_1006_ratio_error<<std::endl;
  }
  else{ //case = benchmark
    file_out<<"Modified = "<<modifier<<", benchmark"<<std::endl;
    NEIL_1006_out<<modifier<<","<<ben<<","<<ben<<","<<NEIL_1006_ratio<<","<<NEIL_1006_ratio_error<<std::endl;
    Flux_1006_out<<modifier<<","<<ben<<","<<ben<<","<<Flux_1006_ratio<<","<<Flux_1006_ratio_error<<std::endl;
    Energy_1006_out<<modifier<<","<<ben<<","<<ben<<","<<Energy_1006_ratio<<","<<Energy_1006_ratio_error<<std::endl;
  }
  std::cout<<"Absolute per event: Neil in Roof 1006 = "<<NEIL_1006<<"("<<NEIL_1006_error<<"), Flux of neutrons to 1006, per million events (E>25.12 MeV) = "<<Flux_1006<<"("<<Flux_1006_error<<"), Energy in 1006 = "<<Energy_1006<<"("<<Energy_1006_error<<")"<<std::endl;
  std::cout<<"Relative per event: Neil in Roof 1006 = "<<NEIL_1006_ratio<<"("<<NEIL_1006_ratio_error<<"), Flux of neutrons to 1006, per million events (E>25.12 MeV) = "<<Flux_1006_ratio<<"("<<Flux_1006_ratio_error<<"), Energy 1006 = "<<Energy_1006_ratio<<"("<<Energy_1006_ratio_error<<")"<<std::endl;
  file_out<<"Absolute per event: Neil in Roof 1006 = "<<NEIL_1006<<", Flux of neutrons to 1006, per million events (E>25.12 MeV) = "<<Flux_1006<<", Energy in 1006 = "<<Energy_1006<<std::endl;
  file_out<<"Relative per event: Neil in Roof 1006 = "<<NEIL_1006_ratio<<", Flux of neutrons to 1006, per million events (E>25.12 MeV) = "<<Flux_1006_ratio<<", Energy 1006 = "<<Energy_1006_ratio<<std::endl;
//print the output and ratio wrt benchmark into the outfile (append)
  file_out.close();
 

  NEIL_1006_out.close();
  Flux_1006_out.close();
  Energy_1006_out.close();
};
