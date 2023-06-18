#############################################################################################################################
#
# File Name: analyzer
# input: input_file     - path of the 1st input assembly file
#        input_file     - path of the 2nd input assembly file
#        outputFile     - path of the output file 
#        min_length     - minimum number of instructions in the sequence   
#        max_length     - maximum number of instructions in the sequence
#        min_repetition - minimum number of repetitions of a sequence to be included
#
# output: file contains all the sequences number of repetion of each sequence (summary)
#         file contains all the sequences , number of repetion of each sequence, number unique repetions, the unique repetions
#
# Description: this file used to get the most frequently executed sequence of instructions in two assembly files.
#              then place the common sequences in the two files in one output file                 
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
                
            # if mm==3:
                # print(sequence)
                # print("\n")
                # print(full_instructions[sequence])
                # print("\n")
                # print(''.join(lines[i:i+length]))
                # x=input()
            # Increment the count for the sequence
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

input_file="readbutton_isr_exe.s"
input_file2="readbutton_exe.s"

outputFile="Report_unique_Repetitions_2files.txt"
min_length = 2   
max_length = 5
min_repetition=10

# do NOT change file_path
file_path = 'extracted_instructions.txt'  # Replace with the path to your file

# do NOT change file_path
file_path2 = 'extracted_instructions2.txt'  # Replace with the path to your file

list_set=extract_instructions(input_file)
write_in_file_all_instructions(file_path,list_set)

sequences,full_lines = find_top_repeated_sequences(file_path, min_length, max_length)

#######################################################################################################

list_set2=extract_instructions(input_file2)
write_in_file_all_instructions(file_path2,list_set2)
sequences2,full_lines2 = find_top_repeated_sequences(file_path2, min_length, max_length)

#sequences2=[mov\npop\npush\nsub\nadd,ldr\nldr\ncmp\nldr\nldr]
with open(outputFile,'w') as file5: 
    for i in range (max_length,min_length-1,-1): 
        st1=[ k for k,v in sequences[i].items()]
        st2=[ k for k,v in sequences2[i].items()]
        sequences3=[e for e in st1 if e in st2]
        file5.write("********************************************* sequence of ")
        file5.write(str(i))
        file5.write(" *********************************************\n")
        for ss in sequences3:
            if(sequences[i][ss]>=10 and sequences2[i][ss]>=10): 
                file5.write(str(ss))
                file5.write("\n")
                file5.write('repetations in first example     : ')
                file5.write(str(sequences[i][ss]))
                file5.write("\n")
                file5.write('repetations in second example    : ')
                file5.write(str(sequences2[i][ss]))
                file5.write("\n")
                file5.write('unique repetations in 2 examples : ')
               
                lis=list(set(full_lines[ss]))
                lis2=list(set(full_lines2[ss]))
                lis3=list(set(lis+lis2))
                
                file5.write(str(len(lis3)))
                file5.write("\n\n")
                for stm in lis3:
                    file5.write(stm)
                    file5.write("\n")
                file5.write(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n")
