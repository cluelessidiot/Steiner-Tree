import networkx as nx
import csv
import matplotlib.pyplot as plt
Data = open('t2.csv', "r")
next(Data, None)  # skip the first line in the input file
Graphtype = nx.Graph()

G = nx.parse_edgelist(Data, delimiter=',', create_using=Graphtype,
                      nodetype=int, data=(('weight', float),))
pos = nx.spring_layout(G)
nx.draw(G,pos,edge_color='black',width=1,linewidths=1,\
node_size=500,node_color='pink',alpha=0.9,\
labels={node:node for node in G.nodes()})
#pos = nx.spring_layout(G)

#labelmap = dict(zip(G.nodes(), ["1", "2", "3", "4"]))
nx.draw_networkx_edge_labels(G,pos,edge_labels={(1,2):G[1][2]['weight'],(1,3):G[1][3]['weight'],(1,4):G[1][4]['weight'],(2,4):G[2][4]['weight'],(3,4):G[3][4]['weight']},font_color='red')
plt.show()

