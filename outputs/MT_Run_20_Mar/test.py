import numpy as np
# Define a dictionary to store variables dynamically
variables = {}

# Example string containing 'an'
string_content = 'an'

# Create the variable name dynamically by appending the string content
variable_name = f"data_array_{string_content}"

# Create your variable (empty NumPy array in this case)
data_array_an = np.zeros((10, 10))  # Example NumPy array

# Assign the variable to the dictionary with the dynamically generated name
variables[variable_name] = data_array_an

# You can access the variable using the dictionary
print(variables[variable_name])
