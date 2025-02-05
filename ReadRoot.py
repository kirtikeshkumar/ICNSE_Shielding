import ROOT
import numpy as np
import matplotlib.pyplot as plt
import code

def read_tree(tree):
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
        branchIndx_map = {}
        for i, branch in enumerate(branches):
            branch_name = branch.GetName()
            branchIndex_map[branch_name] = i
            branchIndx_map[i] = branch_name

        # Create an empty NumPy array to store the data
        data_array = []

        # Loop through each event in the tree
        for i, event in enumerate(tree):
            if(i%100000 == 0):
                print(f"Read Entry {i}")
            data_array.append([])
            # Loop through each branch in the tree
            for j in range(numBranches):
                # Get the value of the branch for the current event and store it in the data array
                data_array[i].append(getattr(event, f"{branchIndx_map[j]}"))
        
        return branchIndx_map, branchIndex_map, data_array, numEntries
    else:
        # If the tree is not loaded, return None
        print("Check the Tree name")
        return None, 0


def read_file(fname):
    # Open the file to read
    root_file = ROOT.TFile.Open(fname)

    # Get the list of keys
    keys = root_file.GetListOfKeys()

    # Create a dictionary storing the different Tree names and corresponding data
    fTrees = {}

    #check if the key is for TTree object and read the data
    for key in keys:
        # Get the object associated with the key
        obj = root_file.Get(key.GetName())  

        # Check if the object is a TTree
        if isinstance(obj, ROOT.TTree):
            fTree_name = key.GetName()                                                      # Get the TTree name
            branchIndx_map, branchIndex_map, data_array, numEntries = read_tree(obj)        # Read the TTree
            fTrees[fTree_name] = (numEntries, branchIndx_map, branchIndex_map, data_array)  # Store the output in a dictionary

    return fTrees
