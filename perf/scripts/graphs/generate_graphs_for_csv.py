# Install Python3 with pip
# Then pip install pandas and pip install matplotlib

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

basePath = "build/perf/graphs/analytics/"
x_rounds = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20])

opNames = ["insert", "search", "delete"]
opNameTexts = {"insert": "Insert", "search": "Search", "delete": "Delete"}

for opName in opNames:
    opNameText = opNameTexts[opName]

    # 1 element graphs
    # 1 element total time graph (with C#)
    inDataFile = basePath+opName+"/test"+opNameText+"1/total.csv"
    outGraphFile = "perf/charts/"+opName+"/1 round/cumuTimeCSharp.pdf"
    df = pd.read_csv(inDataFile)
    df_t = df.set_index('Element').transpose()
    # print(df)
    # print(df_t)

    ax = df_t.plot(kind='line', figsize=(8,5))
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)

    plt.xlabel('Round')
    plt.ylabel('Time complexity millisecs')
    plt.legend()
    plt.xticks(x_rounds)
    fig = ax.get_figure()
    fig.savefig(outGraphFile, bbox_inches='tight', pad_inches=0.1)
    plt.close()

    # 1 element total time graph (without C#)
    inDataFile = basePath+opName+"/test"+opNameText+"1/total.csv"
    outGraphFile = "perf/charts/"+opName+"/1 round/cumuTimeNoCSharp.pdf"
    df = pd.read_csv(inDataFile)
    df_t = df.set_index('Element').transpose()
    df_t_noCS = df_t.drop('C#', axis=1)
    # print(df)
    # print(df_t_noCS)

    ax = df_t_noCS.plot(kind='line', figsize=(8,5))
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)

    plt.xlabel('Round')
    plt.ylabel('Time complexity millisecs')
    plt.legend()
    plt.xticks(x_rounds)
    fig = ax.get_figure()
    fig.savefig(outGraphFile, bbox_inches='tight', pad_inches=0.1)
    plt.close()

    # 1 element total time graph (Swiss implementations)
    inDataFile = basePath+opName+"/test"+opNameText+"1/total.csv"
    outGraphFile = "perf/charts/"+opName+"/1 round/cumuTimeSwiss.pdf"
    df = pd.read_csv(inDataFile)
    df_t = df.set_index('Element').transpose()
    df_t_swiss = df_t.drop(columns=['CPP-Basic', 'Python', 'Java', 'C#'], axis=1)
    # print(df)
    # print(df_t_swiss)

    ax = df_t_swiss.plot(kind='line', figsize=(8,5))
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)

    plt.xlabel('Round')
    plt.ylabel('Time complexity millisecs')
    plt.legend()
    plt.xticks(x_rounds)
    fig = ax.get_figure()
    fig.savefig(outGraphFile, bbox_inches='tight', pad_inches=0.1)
    plt.close()

    # 1 element min,max,avg time graph (with C#)
    inDataFile = basePath+opName+"/test"+opNameText+"1/minmaxavg.csv"
    outGraphFile = "perf/charts/"+opName+"/1 round/MinMaxAvgCSharp.pdf"
    df = pd.read_csv(inDataFile)
    df_el = df.set_index('Element')
    # print(df_element)
    # print(df_t)

    ax = df_el.plot(marker = 'o', figsize=(8,5))
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)

    plt.xlabel('Implementation')
    plt.ylabel('Time complexity millisecs')
    plt.legend()
    fig = ax.get_figure()
    fig.savefig(outGraphFile, bbox_inches='tight', pad_inches=0.1)
    plt.close()

    # 1 element min,max,avg time graph (without C#)
    inDataFile = basePath+opName+"/test"+opNameText+"1/minmaxavg.csv"
    outGraphFile = "perf/charts/"+opName+"/1 round/MinMaxAvgNoCSharp.pdf"
    df = pd.read_csv(inDataFile)
    df_el = df.set_index('Element')
    df_el_noCS = df_el.drop('C#', axis=0)
    # print(df)
    # print(df_el_noCS)

    ax = df_el_noCS.plot(marker = 'o', figsize=(8,5))
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)

    plt.xlabel('Implementation')
    plt.ylabel('Time complexity millisecs')
    plt.legend()
    fig = ax.get_figure()
    fig.savefig(outGraphFile, bbox_inches='tight', pad_inches=0.1)
    plt.close()

    # 1 element min,max,avg time graph (Swiss implementations)
    inDataFile = basePath+opName+"/test"+opNameText+"1/minmaxavg.csv"
    outGraphFile = "perf/charts/"+opName+"/1 round/MinMaxAvgSwiss.pdf"
    df = pd.read_csv(inDataFile)
    df_el = df.set_index('Element')
    # df_el_swiss = df_el.drop(columns=['CPP-Basic', 'Python', 'Java', 'C#'], axis=0)
    df_el_1 = df_el.drop('CPP-Basic', axis=0)
    df_el_2 = df_el_1.drop('Python', axis=0)
    df_el_3 = df_el_2.drop('Java', axis=0)
    df_el_swiss = df_el_3.drop('C#', axis=0)
    # print(df)
    # print(df_el_swiss)

    ax = df_el_swiss.plot(marker = 'o', figsize=(8,5))
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)
    # ax.set_xticklabels(labels=["C", "CPP-Swiss"])

    plt.xlabel('Implementation')
    plt.ylabel('Time complexity millisecs')
    plt.legend()
    fig = ax.get_figure()
    fig.savefig(outGraphFile, bbox_inches='tight', pad_inches=0.1)
    plt.close()

    # 81922 element graphs
    # 81922 element total time graph (with C#)
    inDataFile = basePath+opName+"/test"+opNameText+"81922/total.csv"
    outGraphFile = "perf/charts/"+opName+"/20 rounds/TotalCumuTimeCSharp.pdf"
    df = pd.read_csv(inDataFile)
    df_t = df.set_index('Element').transpose()
    # print(df)
    # print(df_t)

    ax = df_t.plot(kind='line', figsize=(8,5))
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)

    plt.xlabel('Round')
    plt.ylabel('Time complexity millisecs')
    plt.legend()
    plt.xticks(x_rounds)
    fig = ax.get_figure()
    fig.savefig(outGraphFile, bbox_inches='tight', pad_inches=0.1)
    plt.close()

    # 81922 element total time graph (without C#)
    inDataFile = basePath+opName+"/test"+opNameText+"81922/total.csv"
    outGraphFile = "perf/charts/"+opName+"/20 rounds/TotalCumuTimeNoCSharp.pdf"
    df = pd.read_csv(inDataFile)
    df_t = df.set_index('Element').transpose()
    df_t_noCS = df_t.drop('C#', axis=1)
    # print(df)
    # print(df_t_noCS)

    ax = df_t_noCS.plot(kind='line', figsize=(8,5))
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)

    plt.xlabel('Round')
    plt.ylabel('Time complexity millisecs')
    plt.legend()
    plt.xticks(x_rounds)
    fig = ax.get_figure()
    fig.savefig(outGraphFile, bbox_inches='tight', pad_inches=0.1)
    plt.close()

    # 81922 element total time graph (Swiss implementations)
    inDataFile = basePath+opName+"/test"+opNameText+"81922/total.csv"
    outGraphFile = "perf/charts/"+opName+"/20 rounds/TotalCumuTimeSwiss.pdf"
    df = pd.read_csv(inDataFile)
    df_t = df.set_index('Element').transpose()
    df_t_swiss = df_t.drop(columns=['CPP-Basic', 'Python', 'Java', 'C#'], axis=1)
    # print(df)
    # print(df_t_swiss)

    ax = df_t_swiss.plot(kind='line', figsize=(8,5))
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)

    plt.xlabel('Round')
    plt.ylabel('Time complexity millisecs')
    plt.legend()
    plt.xticks(x_rounds)
    fig = ax.get_figure()
    fig.savefig(outGraphFile, bbox_inches='tight', pad_inches=0.1)
    plt.close()

    # 81922 element avg-cumulative time graph (with C#)
    inDataFile = basePath+opName+"/test"+opNameText+"81922/avg-cumulative.csv"
    outGraphFile = "perf/charts/"+opName+"/20 rounds/AvgCumuTimeCSharp.pdf"
    df = pd.read_csv(inDataFile)
    df_t = df.set_index('Element').transpose()
    # print(df)
    # print(df_t)

    ax = df_t.plot(kind='line', figsize=(8,5))
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)

    plt.xlabel('Number of elements')
    plt.ylabel('Time complexity millisecs')
    plt.legend()
    fig = ax.get_figure()
    fig.savefig(outGraphFile, bbox_inches='tight', pad_inches=0.1)
    plt.close()

    # 81922 element avg-cumulative time graph (without C#)
    inDataFile = basePath+opName+"/test"+opNameText+"81922/avg-cumulative.csv"
    outGraphFile = "perf/charts/"+opName+"/20 rounds/AvgCumuTimeNoCSharp.pdf"
    df = pd.read_csv(inDataFile)
    df_t = df.set_index('Element').transpose()
    df_t_noCS = df_t.drop('C#', axis=1)
    # print(df)
    # print(df_t_noCS)

    ax = df_t_noCS.plot(kind='line', figsize=(8,5))
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)

    plt.xlabel('Number of elements')
    plt.ylabel('Time complexity millisecs')
    plt.legend()
    fig = ax.get_figure()
    fig.savefig(outGraphFile, bbox_inches='tight', pad_inches=0.1)
    plt.close()

    # 81922 element avg-cumulative time graph (Swiss implementations)
    inDataFile = basePath+opName+"/test"+opNameText+"81922/avg-cumulative.csv"
    outGraphFile = "perf/charts/"+opName+"/20 rounds/AvgCumuTimeSwiss.pdf"
    df = pd.read_csv(inDataFile)
    df_t = df.set_index('Element').transpose()
    df_t_swiss = df_t.drop(columns=['CPP-Basic', 'Python', 'Java', 'C#'], axis=1)
    # print(df)
    # print(df_t_swiss)

    ax = df_t_swiss.plot(kind='line', figsize=(8,5))
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)

    plt.xlabel('Number of elements')
    plt.ylabel('Time complexity millisecs')
    plt.legend()
    fig = ax.get_figure()
    fig.savefig(outGraphFile, bbox_inches='tight', pad_inches=0.1)
    plt.close()

print("===== Completed =====")