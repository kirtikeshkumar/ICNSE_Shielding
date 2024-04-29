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
        for i, branch in enumerate(branches):
            branch_name = branch.GetName()
            branchIndex_map[i] = branch_name

        # Create an empty NumPy array to store the data
        data_array = []

        # Loop through each event in the tree
        for i, event in enumerate(tree):
            data_array.append([])
            # Loop through each branch in the tree
            for j in range(numBranches):
                # Get the value of the branch for the current event and store it in the data array
                data_array[i].append(getattr(event, f"{branchIndex_map[j]}"))
        
        return branchIndex_map, data_array, numEntries
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
            fTree_name = key.GetName()                                      # Get the TTree name
            branchIndex_map, data_array, numEntries = read_tree(obj)        # Read the TTree
            fTrees[fTree_name] = (numEntries, branchIndex_map, data_array)  # Store the output in a dictionary

    return fTrees

##################################################################################################################
##                                             MAIN PROGRAM                                                     ##
##################################################################################################################
# Define the properties of simulation
particle    = 'neutron'
ordering    = 'HHBBLLHH'
numSimEvt   = 1000000
minEnergy   = 100
maxEnergy   = 3700
energyStep  = 400

# Variable containing the required data
numParticleInSensVol = []

currEnergy = minEnergy
while(currEnergy <= maxEnergy):                                             # Loop over the energies
    fname = f"{particle}/output_{particle}_{currEnergy}keV_{ordering}_{numSimEvt}evt.root"
    fTrees = read_file(fname)
    if(fTrees):
        keys = list(fTrees.keys())                                          # Get the list of Tree names in the file
        if(keys):                                                           # If no particles traverse then no tree is created. Hence checking if the trees exist
            vals = [currEnergy]
            for key in keys:                                                # Read the number of particles transmitting to sensitive volume 
                if(fTrees[key][0]):
                    vals.append(fTrees[key][0])
                else:
                    vals.append(0)
            numParticleInSensVol.append(vals)
    currEnergy += energyStep

listNumParticle = np.transpose(numParticleInSensVol)
for i,key in enumerate(keys):
    if(key != 'Neutrinos' and key != 'antiNeutrinos'):
        plt.semilogy(listNumParticle[0],listNumParticle[i+1]/numSimEvt,label=f"{key}")
##        plt.plot(listNumParticle[0],listNumParticle[i+1]/numSimEvt,label=f"{key}")
plt.xlabel(f"Incident {particle} Energy [keV]")
plt.ylabel("# of Particles reaching sens vol/Incident")
plt.legend(fontsize=15)
plt.savefig(f"LogTransmissionSpectraForIncident_{particle}.pdf")
##plt.savefig(f"TransmissionSpectraForIncident_{particle}.pdf")
plt.show()
# Start an interactive interpreter session with access to local variables
code.interact(local=locals())
