# Shell Script to run ProducerConsumer using a 6 second wait time.
# Outputs all data to a file 16sec-output.txt

./PRODUCER-CONSUMER/ProducerConsumer 6 1 1 > PRODUCER-CONSUMER/6sec-output.txt
./PRODUCER-CONSUMER/ProducerConsumer 6 1 4 >> PRODUCER-CONSUMER/6sec-output.txt
./PRODUCER-CONSUMER/ProducerConsumer 6 1 16 >> PRODUCER-CONSUMER/6sec-output.txt
./PRODUCER-CONSUMER/ProducerConsumer 6 4 1 >> PRODUCER-CONSUMER/6sec-output.txt
./PRODUCER-CONSUMER/ProducerConsumer 6 4 4 >> PRODUCER-CONSUMER/6sec-output.txt
./PRODUCER-CONSUMER/ProducerConsumer 6 4 16 >> PRODUCER-CONSUMER/6sec-output.txt
./PRODUCER-CONSUMER/ProducerConsumer 6 16 1 >> PRODUCER-CONSUMER/6sec-output.txt
./PRODUCER-CONSUMER/ProducerConsumer 6 16 4 >> PRODUCER-CONSUMER/6sec-output.txt
./PRODUCER-CONSUMER/ProducerConsumer 6 16 16 >> PRODUCER-CONSUMER/6sec-output.txt