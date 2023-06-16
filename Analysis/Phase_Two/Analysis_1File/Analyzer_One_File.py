#############################################################################################################################
#
# File Name: analyzer
# input: input_file     - path of the input assembly file 
#        outputFile     - path of the 1st output file (summary)
#        outputFile2     - path of the 2nd output file (Report_unique_Repetitions)
#        min_length     - minimum number of instructions in the sequence   
#        max_length     - maximum number of instructions in the sequence
#        min_repetition - minimum number of repetitions of a sequence to be included
#
# output: file contains all the sequences number of repetion of each sequence (summary)
#         file contains all the sequences , number of repetion of each sequence, number unique repetions, the unique repetions
#
# Description: this file used to get the most frequently executed sequence of instructions in a assembly file.  
#              
#############################################################################################################################


from collections import defaultdict

def extract_instructions(fileName) :
    list_set =[]
    with open(fileName, "r") as file:
        for line in file:
            words= line.split()
            if len(words)>3:
                if len(words[2])!=8 and words[2].find(".")==-1 and words[2].find("sectio")==-1:
                    list_set.append(line[20:])
    return list_set
    
def write_in_file_all_instructions (fileName, list_set ):
    with open (fileName, "w") as newfile:
        for line in list_set:
            newfile.write(str(line))
 
def find_top_repeated_sequences(file_path, min_length, max_length):
    sequence_counts = []
    full_instructions={}
    for i in range (0,max_length+1):
        sequence_counts.append({})
        
    # Read the file
    with open(file_path, 'r') as file:
        lines = file.readlines()
   
    # Iterate through each line in the file
    for i in range(len(lines) - max_length + 1):
        # Create sequences of different lengths
        for length in range(min_length, max_length + 1):
            seq=''
            for j in range(i,i+length):
                seq +=lines[j].split()[0]+'\n'
            sequence = ''.join(seq)
            
            if sequence not in full_instructions:
                full_instructions[sequence] = [''.join(lines[i:i+length])]
            else:
                full_instructions[sequence].append(''.join(lines[i:i+length]))

            sequence_counts[length][sequence] = sequence_counts[length].get(sequence,0)+1
            

    
    
    return sequence_counts ,full_instructions

def write_in_file_sequence_of_instructions(fileName,sequences,counts,min_repetition):
    with open(fileName,'w') as file2:
        for i in range(len(sequences)):
            
            if counts[i] >= min_repetition:
                file2.write("Sequence: \n")
                file2.write(sequences[i])
                file2.write("Repetition count: ")
                file2.write(str(counts[i]))
                file2.write("\n\n###########################################################\n")




# Usage example

input_file="lonely_exe.s"
outputFile="summary.txt"
outputFile2="Report_unique_Repetitions.txt"
min_length = 2   
max_length = 5
min_repetition=10

# do NOT change file_path
file_path = 'extracted_instructions.txt'  # Replace with the path to your file

list_set=extract_instructions(input_file)
write_in_file_all_instructions(file_path,list_set)

sequences,full_lines = find_top_repeated_sequences(file_path, min_length, max_length)



# Find the top repeated sequences
with open(outputFile,'w') as file2:
    for i in range (max_length,min_length-1,-1):
        sequences[i] = sorted([(v,k) for k,v in sequences[i].items()], reverse=True)
        file2.write(" ************************************** Sequences of ")
        file2.write(str(i))
        file2.write(" consecutive instructions ************************************** ")
        for value,key in sequences[i]:
            if value >= min_repetition:
                file2.write("\nSequence: \n")
                file2.write(key)
                file2.write("Repetition count: ")
                file2.write(str(value))
                file2.write("\n\n#################################\n")

# Find the top repeated sequences
# with open("Report_all_Repetitions.txt",'w') as file3:
    
    # for i in range (max_length,min_length-1,-1):
        # file3.write(" ************************************** Sequences of ")
        # file3.write(str(i))
        # file3.write(" consecutive instructions ************************************** ")
        # for value,key in sequences[i]:
            # if value >= min_repetition:
                # file3.write("\nSequence: \n")
                # file3.write(key)
                # file3.write("Repetition count: ")
                # file3.write(str(value))
                # file3.write("\n\n")
                
                # for line in full_lines[key]:
                    # file3.write(line)
                    # file3.write("\n###################\n")
                # file3.write("\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n") 
            
            
# Find the top repeated sequences
with open(outputFile2,'w') as file4:   
    for i in range (max_length,min_length-1,-1):
        file4.write(" ************************************** Sequences of ")
        file4.write(str(i))
        file4.write(" consecutive instructions ************************************** ")
        for value,key in sequences[i]:
            if value >= min_repetition:
                file4.write("\nSequence: \n")
                file4.write(key)
                file4.write("Repetition count: ")
                file4.write(str(value))
                file4.write("\nunique Repetitions ")
                file4.write(str(len(set(full_lines[key]))))
                file4.write("\n\n")
                for line in set(full_lines[key]):
                    file4.write(line)
                    file4.write("\n###################\n")
                file4.write("\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n") 
            
