import java.io.*;
import java.util.*;
import java.util.stream.IntStream;

public class Solution {
    static class Graph {
        Map<Integer, List<Integer>> neighs;
        Map<Edge, Integer> edges;

        Graph(Map<Integer, List<Integer>> neighs, Map<Edge, Integer> edges) {
            this.neighs = neighs;
            this.edges = edges;
        }
    }

    static class Dist implements Comparable<Dist> {
        int value;
        int vertex;

        Dist(int value, int vertex) {
            this.value = value;
            this.vertex = vertex;
        }

        @Override
        public int compareTo(Dist other) {
            return this.value - other.value;
        }

        @Override
        public boolean equals(Object other) {
            return this.vertex == ((Dist)other).vertex;
        }
    }

    static class Edge {
        int v1;
        int v2;

        @Override
        public int hashCode() {
            return v1 * v2;
        }

        @Override
        public boolean equals(Object obj) {
            Edge other = (Edge)obj;
            return (v1 == other.v1 && v2 == other.v2) || (v1 == other.v2 && v2 == other.v1);
        }

        public Edge(int v1, int v2) {
            this.v1 = v1;
            this.v2 = v2;
        }
    }

    static int[] shortestReach(int n, int[][] edges, int s) {
        int[] result = new int[n - 1];
        int i = 0;

        Map<Integer, Integer> dist = distances(graph(edges), s);

        for (int v = 1; v <= n; v++) {
            if (v == s) continue;
            result[i] = dist.containsKey(v) ? dist.get(v) : -1;
            i++;
        }

        return result;
    }

    private static Map<Integer, Integer> distances(Graph g, int source) {
        Queue<Dist> q = new PriorityQueue<>();
        q.add(new Dist(0, source));

        Map<Integer, Integer> dist = new HashMap<>();
        dist.put(source, 0);


        while (q.size() > 0) {
            int current = q.poll().vertex;

            for (int adjacent : g.neighs.get(current)) {
                int alt = dist.get(current) + g.edges.get(new Edge(current, adjacent));

                if (alt < (dist.containsKey(adjacent) ? dist.get(adjacent) : Integer.MAX_VALUE)) {
                    Dist alteredDist = new Dist(alt, adjacent);
                    q.remove(alteredDist);
                    q.add(alteredDist);
                    dist.put(adjacent, alt);
                }
            }
        }

        return dist;
    }

    private static Graph graph(int[][] rows) {
        Map<Integer, List<Integer>> neighs = new HashMap<>();
        Map<Edge, Integer> edges = new HashMap<>();

        for (int[] triplet : rows) {
            if (!neighs.containsKey(triplet[0])) {
                neighs.put(triplet[0], new ArrayList<>());
            }

            if (!neighs.containsKey(triplet[1])) {
                neighs.put(triplet[1], new ArrayList<>());
            }

            neighs.get(triplet[0]).add(triplet[1]);
            neighs.get(triplet[1]).add(triplet[0]);

            Edge e = new Edge(triplet[0], triplet[1]);
            if (!edges.containsKey(e) || edges.get(e) > triplet[2]) {
                edges.put(e, triplet[2]);
            }
        }

        return new Graph(neighs, edges);
    }

    private static final BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String[] args) throws IOException {
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int t = Integer.parseInt(reader.readLine());

        for (int tItr = 0; tItr < t; tItr++) {
            String[] nm = reader.readLine().split(" ");

            int n = Integer.parseInt(nm[0]);

            int m = Integer.parseInt(nm[1]);

            int[][] edges = new int[m][3];

            for (int i = 0; i < m; i++) {
                String[] edgesRowItems = reader.readLine().split(" ");

                for (int j = 0; j < 3; j++) {
                    int edgesItem = Integer.parseInt(edgesRowItems[j]);
                    edges[i][j] = edgesItem;
                }
            }

            int s = Integer.parseInt(reader.readLine());

            int[] result = shortestReach(n, edges, s);

            for (int i = 0; i < result.length; i++) {
                bufferedWriter.write(String.valueOf(result[i]));

                if (i != result.length - 1) {
                    bufferedWriter.write(" ");
                }
            }

            bufferedWriter.newLine();
        }

        bufferedWriter.close();

        reader.close();
    }
}
