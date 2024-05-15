document.getElementById('uploadButton').addEventListener('click', function() {
    var fileInput = document.getElementById('fileInput');
    var file = fileInput.files[0];
    if (!file) return;

    //var chunkSize = 1 * 1024 * 1024; // 设置为2MB的块
    var chunkSize = 1 * 1024; // 设置为1KB的块
    var totalSize = file.size;
    var totalChunks = Math.ceil(totalSize / chunkSize);
    var currentChunk = 0;

    var progressBar = document.getElementById('progressBar');

    console.log(totalChunks);

    function uploadNextChunk() {
        var start = currentChunk * chunkSize;
        var end = Math.min(start + chunkSize, totalSize);
        var chunk = file.slice(start, end);
        var formData = new FormData();
        formData.append('file', chunk);
        formData.append('currentChunk', currentChunk + 1);
        formData.append('totalChunks', totalChunks);

        fetch('/', { // 注意这里的URL应该是服务器端处理上传的端点
            method: 'POST',
            body: formData
        })
        .then(response => {
            if (!response.ok) {
                throw new Error('上传出错：' + response.statusText);
            }
            return response; // 需要返回response，以便在then链中使用
        })
        .then(() => {
            currentChunk++;
            if (currentChunk < totalChunks) {
                var percentComplete = (currentChunk / totalChunks) * 100;
                progressBar.style.width = percentComplete + '%';
                uploadNextChunk();
            } else {
                progressBar.style.width = '100%';
                alert('文件上传完成！');
            }
        })
        .catch(error => {
            alert('上传出错：' + error.message);
        });
    }

    uploadNextChunk();
});

document.getElementById('fileInput').addEventListener('change', function() {
    document.getElementById('uploadButton').disabled = false;
});