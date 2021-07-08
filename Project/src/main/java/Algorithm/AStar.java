package Algorithm;

import Resource.*;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.PriorityQueue;

public class AStar {

    public static Iterator execute(Graph graph, Point s, Point e) {

        PriorityQueue<QueuePair> queue = new PriorityQueue<>(new Comparator<QueuePair>() {
            @Override
            public int compare(QueuePair o1, QueuePair o2) {
                return o1.priority - o2.priority;
            }
        });
        HashMap<Point, Integer> lengths = new HashMap<>();
        HashMap<Point, Point> paths = new HashMap<>();
        ArrayList<Step> steps = new ArrayList<>();
        Point curr;

        queue.add(new QueuePair(0, s));
        lengths.put(s, 0);
        paths.put(e, null);

        // Основная часть

        while(!queue.isEmpty()) {

            curr = queue.poll().point;
            if (curr.equals(e)) break;

            for (Point i : graph.getMap().get(curr).keySet()) {

                Integer newlen = lengths.get(curr) + graph.getMap().get(curr).get(i);
                if (!lengths.containsKey(i) || newlen < lengths.get(i)) {

                    lengths.put(i, newlen);
                    queue.add(new QueuePair(newlen + heuristic(e, i), i));
                    paths.put(i, curr);
                }
            }

            ArrayList<Point> opened = new ArrayList<>();
            for (QueuePair i : queue) opened.add(i.point);
            ArrayList<Point> closed = new ArrayList<>();
            for (Point i : lengths.keySet()) closed.add(i);
            steps.add(new Step(closed, opened, curr));
        }

        return new Iterator(steps);
    }

    public static int heuristic(Point goal, Point curr) {

        return Math.abs(goal.getX() - curr.getX()) + Math.abs(goal.getY() - curr.getY());
    }

    // -- Классы --

    public static class QueuePair {

        public int priority;
        public Point point;

        public QueuePair(int priority, Point point) {
            this.priority = priority;
            this.point = point;
        }
    }

    public static class Iterator {

        private ArrayList<Step> steps;
        private int index;

        private Iterator(ArrayList<Step> steps) {
            this.steps = steps;
            index = 0;
        }

        public Step next() {

            if (index < steps.size() - 1) index++;
            return steps.get(index);
        }
        public Step curr() {

            return steps.get(index);
        }
        public Step prev() {

            if (index > 0) index--;
            return steps.get(index);
        }
    }

    public static class Step {

        private ArrayList<Point> closed;
        private ArrayList<Point> opened;
        private Point current;

        public Step(ArrayList<Point> closed, ArrayList<Point> opened, Point current) {
            this.closed = closed;
            this.opened = opened;
            this.current = current;
        }

        public ArrayList<Point> getOpened() {

            return opened;
        }
        public ArrayList<Point> getClosed() {

            return closed;
        }
        public Point getCurrent() {

            return current;
        }
    }
}

