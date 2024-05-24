"""
Projeto 3 de Análise e Sintese de Algoritmos
    Realizado por:
    - Carlota Ribeiro Domingos ist1107016
    - David Costa Quintino ist1107095
"""
from pulp import *

line0 = input().split()
toy_types = int(line0[0])
num_combos = int(line0[1])
max_toys = int(line0 [2])

num_variables = toy_types + num_combos

profits = [0]
capacity = [0]
appearances = {}
combo_dict = {}
toys = range(1, num_variables +1)

for i in range(1, toy_types + 1):
    line = input().split()

    appearances[i] = [i]
    profits.append(int(line[0]))
    capacity.append( int(line[1]))

for i in range(toy_types + 1, num_variables + 1):
    line = input().split() 
    combo_specs = [int(line[0]),int(line[1]),int(line[2])]
    combo_dict[i] = combo_specs
    combo_capacity = [capacity[a] for a in combo_specs]
    capacity.append(min(combo_capacity))

    profits.append(int(line[3]))


vars = LpVariable.dicts("toy", toys, None, None, LpInteger)

for a in toys:
    vars[a].bounds(0,capacity[a])


prob = LpProblem("Toys", LpMaximize)

prob += lpSum(vars[a]* profits[a] for a in toys), "Total profit"

prob += lpSum(vars[a] for a in range(1, toy_types + 1)) + lpSum(3*vars[a] for a in range(toy_types + 1, num_variables + 1)) <= max_toys, "Not excedding the max number of toys"



for key,specs in combo_dict.items():
    for x in specs:
        appearances[x].append(key)

for key in appearances:
    prob += lpSum(vars[toy] for toy in appearances[key]) <= capacity[key] , "okok" + str(key)


prob.writeLP("Prob.txt")    
prob.solve(GLPK(msg=0))
print(value(prob.objective))
