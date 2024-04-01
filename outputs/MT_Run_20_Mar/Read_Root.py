# Import necessary libraries
import ROOT                                     # ROOT is a data analysis framework used in high-energy physics
import numpy as np                              # NumPy is a library for numerical computations in Python
import matplotlib.pyplot as plt                 # Matplotlib is a plotting library for Python
import code                                     # Code module provides an interactive interpreter console

# Open the ROOT file containing the data
root_file = ROOT.TFile.Open("neutron/output_neutron_4000keV_HHBLHBLH_10000000evt.root")

# Get the tree named "antiNeutrinos" from the ROOT file
tree = root_file.Get("antiNeutrinos")

# Check if the tree is successfully loaded
if tree:
    # Get the total number of entries in the tree
    numEntries = tree.GetEntries()
    
    # Get the list of branches in the tree
    branches = tree.GetListOfBranches()
    
    # Get the total number of branches
    numBranches = len(branches)
    
    # Create a dictionary to map branch indices to their names
    branchIndex_map = {}
    for i, branch in enumerate(branches):
        branch_name = branch.GetName()
        branchIndex_map[i] = branch_name
    
    # Create an empty NumPy array to store the data
    data_array = np.empty((numEntries, numBranches))
    
    # Loop through each event in the tree
    for i, event in enumerate(tree):
        # Loop through each branch in the tree
        for j in range(numBranches):
            # Get the value of the branch for the current event and store it in the data array
            data_array[i, j] = getattr(event, f"{branchIndex_map[j]}")
else:
    # If the tree is not loaded, print an error message
    print("Check the Tree name")

# Start an interactive interpreter session with access to local variables
code.interact(local=locals())
