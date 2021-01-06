#!/usr/bin/env python
# coding: utf-8

# In[1]:


# CSCI3220 2020-21 First Term Assignment 4
# I declare that the assignment here submitted is original except for source
# material explicitly acknowledged, and that the same or closely related material
# has not been previously submitted for another course. I also acknowledge that I
# am aware of University policy and regulations on honesty in academic work, and
# of the disciplinary guidelines and procedures applicable to breaches of such
# policy and regulations, as contained in the following websites.
# University Guideline on Academic Honesty:
# http://www.cuhk.edu.hk/policy/academichonesty/
# Student Name: LI Jialu
# Student ID : 1155107895


# In[ ]:


# read the input from the user 
# store them as a list of string 
input_string = []
input_string.append(input().replace(',',''))

length = len(input_string[0].replace(',',''))

for i in range(length):
    input_string.append(input().replace(',',''))


# In[ ]:


# construct a distance dictionary from the input 
# the advantage of dictionary over matrix: each data is only stored once and easy to find data 
dist_dict = {}
for i in range(0,len(input_string)-2):
    sub_dict = {}
    for j in range(i+1,len(input_string)-1):
        sub_dict[input_string[0][j]] = input_string[i+1][j+1]
    dist_dict[input_string[0][i]] = sub_dict

# construct the dictionary again at beginning 
# use it as reference 
dist_dict_ref = {}
for i in range(0,len(input_string)-2):
    sub_dict= {}
    for j in range(i+1,len(input_string)-1):
        sub_dict[input_string[0][j]] = input_string[i+1][j+1]
    dist_dict_ref[input_string[0][i]] = sub_dict

# all the row titles in the dictionary 
rows = list(input_string[0].replace(',',''))


# In[ ]:


# convert a list of strings to a string 
def listToString(s):  
    str1 = ""  
    for e in s:  
        str1 += e.replace(',','').replace('(','').replace(')','')
    return str1  


# In[ ]:


# find the minimal value in the dictionary 

def find_min_dist (dist_dict):
    min_value = float("inf")
    strings = []
    for [k,v] in dist_dict.items():  
        
        for [i,j] in v.items():
            if float(j) == min_value:                
                #print(str(j)+'='+str(min_value))
                if sorted(i) < sorted(k):
                    strings.append([i,k])
                else:
                    strings.append([k,i])
                    
            if float(j) < min_value:
                min_value = float(j)
                strings = []
                #print(str(j)+'<'+str(min_value))
                if sorted(i,reverse =True) < sorted(k,reverse =True):
                    strings.append([i,k])
                else:
                    strings.append([k,i])
    
    # if there are two value equal 
    # find the one with lexicographically smaller label 
    output_string = []
    if(len(strings) == 1):
        output_string = strings[0]
    else:    
        output_string = strings[0]
        bc = sorted(listToString(strings[0]))    
        for s in strings:
            string_s = listToString(s)
            ans = sorted(listToString(s))
            if ans < bc:
                output_string = s
              
    return output_string


# In[ ]:


# convert the raw output to the output in the requied form 
# For example, convert ['A','D'] to(A,D)

def convert_output(output_string):
    key1 = output_string[0]
    key2 = output_string[1]
    key1_raw = key1.replace(',','').replace('(','').replace(')','')
    key2_raw = key2.replace(',','').replace('(','').replace(')','')
    converted_output = ''
    if sorted(key1_raw) < sorted(key2_raw):
        converted_output =  ('(' + key1  + ',' + key2 +')')
    else:
        converted_output =  ('(' + key2  + ',' + key1 +')')
        
    return converted_output


# In[ ]:


# calculate the average of a list of numbers 

def average(list):
    summ = 0 
    for l in list:
        summ = summ + l 
    return float(summ) / len(list)


# In[ ]:


# when we find the minimal value in the dictionary 
# we have to create a new sub_dictionary for it 
# For example, if min value = AD, we have to create an entry for (A,D)
# and calculate ((A,D),B) ((A,D),C)
# here we define chars like (A,D) as output_string 
# define chars like B as row 

def add_rows (dist_dict,rows,output_string,converted_output):
    
    # if don't have to map (A,D) to A or D 
    # so delete them from the rows 
    key1 = str(output_string[0])
    key2 = str(output_string[1])
    if str(key1) in rows:
        rows.remove(key1)
    else:pass
    if str(key2) in rows:
        rows.remove(key2)
    else:pass
    
    # create a new entry for the closest pair, eg. AD 
    sub_dict = {}
    for row in rows:
        avg_list = [] 
        chars = list(row.replace(',','').replace('(','').replace(')',''))
        for char in chars:     
            string = listToString(output_string)
            for key in list(string):
                if (key in dist_dict_ref.keys()) and (char in dist_dict_ref[key].keys()):
                    #print(str(key)+str(char)+str(dist_dict_ref[key][char]))
                    avg_list.append(float(dist_dict_ref[key][char]))   
                elif (char in dist_dict_ref.keys()) and (key in dist_dict_ref[char].keys()):
                    avg_list.append(float(dist_dict_ref[char][key]))
                    #print(str(char)+str(key)+str(dist_dict_ref[char][key]))
                else:
                     avg_list.append(100000)

        avg = average(avg_list)
        sub_dict[row] = avg
    
    dist_dict[converted_output] = sub_dict
    rows = rows.append(str(converted_output))
    
    return(dist_dict)


# In[ ]:


# update the dicitonary every time when earase the minimal value 
# For example, if the minimal value is the distance between A and D 

def update_dict (dist_dict,rows,output_string,converted_output):

    dist_dict = add_rows(dist_dict,rows,output_string,converted_output)
    
    key1 = str(output_string[0])
    key2 = str(output_string[1])
    
    # pop the sub dictionary of A and D 
    if key1 in dist_dict.keys():
        dist_dict.pop(key1)
    else: 
        pass
    if key2 in dist_dict.keys():
        dist_dict.pop(key2)
    else: 
        pass
    
   
    # pop the entries in sub dictionaries of A and D 
    for sub_dict in dist_dict:
        if key1 in dist_dict[sub_dict].keys():
            dist_dict[sub_dict].pop(key1)
        else: pass        
        if key2 in dist_dict[sub_dict].keys():
            dist_dict[sub_dict].pop(key2)
        else: pass
    
    
    # if the whole dictionary only have one element 
    # it's time to output the final result 
    if (len(dist_dict) == 1):
        [[key, value]] = dist_dict.items()
        if bool(value) == False:
            print(str(key)+';')
            return 1
        else:
            [[subkey,subvalue]] = value.items()
            print(convert_output([str(key),str(subkey)])+';')
            return 1
    
    # if a whole sub dictionary is empty, then remove this sub dictionary 
    # can't change the object during a loop, so store all sub dictionary have to be popped in pop[] 
    pop = []
    for sub_dict in dist_dict:  
        if bool(dist_dict[str(sub_dict)]) == False:
            pop.append(str(sub_dict))
        else: pass 
    for p in pop:
        dist_dict.pop(p)
    
    if(len(dist_dict) == 0):
        return 1
    
    # return the updated distance dictionary
    return(dist_dict)


# In[ ]:


while (True):
    # while the dictionary don't only one element 
    # continuously update the dictionary by earase the minimal value 
    
    output_string = find_min_dist(dist_dict)
    converted_output = convert_output(output_string)
    if(update_dict(dist_dict, rows, output_string,converted_output) == 1):
        break

