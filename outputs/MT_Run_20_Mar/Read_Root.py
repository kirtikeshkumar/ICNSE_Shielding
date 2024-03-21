import ROOT
import numpy as np
import matplotlib.pyplot as plt
import code

root_file = ROOT.TFile.Open("output_neutron_4000keV_HHBLHBLH_10000000evt.root")
tree = root_file.Get("antiNeutrinos")

if(tree):
    numEntries = tree.GetEntries()
    branches = tree.GetListOfBranches()
    numBranches = len(branches)
    branchIndex_map = {}
    for i, branch in enumerate(branches):
        branch_name = branch.GetName()
        branchIndex_map[i] = branch_name
    data_array = np.empty((numEntries, numBranches))
    for i, event in enumerate(tree):
        for j in range(numBranches):
            data_array[i, j] = getattr(event, f"{branchIndex_map[j]}")
else:
    print("Check the Tree name")


code.interact(local=locals())
