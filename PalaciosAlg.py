def find_atoms(K):
    n = len(K)
    #Find all the indices with positive entries
    remaining_pairs = set((i, j) for i in range(n) for j in range(n) if K[i][j] > 0)

    #Create a list of all sets of chosen index pairs
    M_list = []

    while remaining_pairs:
        #Create the (initially empty) set of chosen index pairs
        M = set()
        #Choose an aritrary index pair which has not been processed yet
        i0, j0 = remaining_pairs.pop()  # Wähle ein beliebiges verbleibendes Paar
        M.add((i0, j0))

        # Liste der neuen Paare, die hinzugefügt werden
        new_pairs = {(i0, j0)}
 
        while new_pairs:
            current_pairs = new_pairs.copy()
            new_pairs.clear()

            for i, j in current_pairs:
                #Add all the index pairs (i,j0), (i0,j) for which K(i,j0), K(i0,j) > 0
                for k in range(n):
                    #iterate through column j:
                    if K[k][j] > 0 and (k, j) not in M:
                        M.add((k, j))
                        new_pairs.add((k, j))
                    #iterate through row i
                    if K[i][k] > 0 and (i, k) not in M:
                        M.add((i, k))
                        new_pairs.add((i, k))

            #Remove added pairs from the remaining ones
            remaining_pairs -= M

        M_list.append(M)

    return M_list


def find_classes(K):
    atoms = find_atoms(K)
    result = [{tup[1] for tup in s} for s in atoms]
    return result

