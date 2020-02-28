import os

FF, IG, DBLP, EP, NET, OR, TW = "FF", "IG", "DBLP", "EP", "NET", "ORKUT", "TW"

GRAPHS = {
    FF: "FriendFeed/",
    IG: "InstagramLCC/",
    EP: "Epinions/",
    DBLP: "DBLP/", 
    NET: "nethept/",
    TW: "Twitter/"
}

H = [2,3,4,5]

def main():
    for g, g_ in GRAPHS.items():
        for h in H:
            g_path = os.path.join('../res', g_, 'graph_ic.inf')
            g_out_path = ".".join(["_".join([g_.strip('/'), 'dgk', str(h)]), 'csv'])
            g_out_path = os.path.join('../output', g_, 'dgk', g_out_path)
            print("{} {} {}".format(g_path, g_out_path, h))





if __name__ == "__main__":
    main()


